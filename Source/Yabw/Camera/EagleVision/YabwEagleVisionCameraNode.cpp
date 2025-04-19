// Copyright 2019-Present tarnishablec. All Rights Reserved.

#include "YabwEagleVisionCameraNode.h"

#include "Core/CameraEvaluationContext.h"
#include "Kismet/KismetMathLibrary.h"

namespace Yabw
{
	UE_DEFINE_CAMERA_NODE_EVALUATOR(FYabwEagleVisionCameraNodeEvaluator)

	void FYabwEagleVisionCameraNodeEvaluator::OnInitialize(
		const UE::Cameras::FCameraNodeEvaluatorInitializeParams& Params,
		UE::Cameras::FCameraNodeEvaluationResult& OutResult)
	{
		const auto* Node = GetCameraNodeAs<UYabwEagleVisionCameraNode>();

		YawInputReader.Initialize(Node->YawInput);
		YawScaleReader.Initialize(Node->YawSpeed);
		PitchInputReader.Initialize(Node->PitchInput);
		PitchScaleReader.Initialize(Node->PitchSpeed);
		ZoomInputReader.Initialize(Node->ZoomInput);
		ZoomScaleReader.Initialize(Node->ZoomSpeed);
		PitchAngleClampReader.Initialize(Node->PitchAngleClamp);
		ArmLengthClampReader.Initialize(Node->ArmLengthClamp);

		RootOffset = Node->InitialRootOffset.Variable->DefaultValue;
		LookAtOffset = Node->InitialLookAtOffset.Variable->DefaultValue;
	}

	void FYabwEagleVisionCameraNodeEvaluator::OnRun(const UE::Cameras::FCameraNodeEvaluationParams& Params,
	                                                UE::Cameras::FCameraNodeEvaluationResult& OutResult)
	{
		const auto* PlayerController = Params.EvaluationContext->GetPlayerController();
		if (!ensure(PlayerController))
		{
			return;
		}

		const auto* Pawn = PlayerController->GetPawnOrSpectator();
		if (!ensure(Pawn))
		{
			return;
		}

		const auto& PawnTransform = FTransform(Pawn->GetActorLocation());
		auto& CameraPose = OutResult.CameraPose;


		const auto PitchInput = PitchInputReader.Get(OutResult.VariableTable);
		const auto PitchScale = PitchScaleReader.Get(OutResult.VariableTable);

		const auto YawInput = YawInputReader.Get(OutResult.VariableTable);
		const auto YawScale = YawScaleReader.Get(OutResult.VariableTable);

		const auto ZoomInput = ZoomInputReader.Get(OutResult.VariableTable);
		const auto ZoomScale = ZoomScaleReader.Get(OutResult.VariableTable);

		const auto PitchAngleClamp = PitchAngleClampReader.Get(OutResult.VariableTable);
		const auto ArmLengthClamp = ArmLengthClampReader.Get(OutResult.VariableTable);

		const auto DeltaTime = Params.DeltaTime;

		const auto PreRootRotator = RootOffset.Rotator();
		RootOffset.SetRotation(
			FQuat::MakeFromRotator(FRotator(
				PreRootRotator.Pitch,
				PreRootRotator.Yaw + YawInput * YawScale,
				PreRootRotator.Roll
			)));

		const auto PreLookAtRotator = LookAtOffset.Rotator();
		LookAtOffset.SetRotation(
			FQuat::MakeFromRotator(FRotator(
				FMath::Clamp(
					PreLookAtRotator.Pitch + PitchInput * PitchScale,
					PitchAngleClamp.GetMin(),
					PitchAngleClamp.GetMax()
				),
				PreLookAtRotator.Yaw,
				PreLookAtRotator.Roll
			))
		);

		const auto RootTransform = RootOffset * PawnTransform;

		TargetArmRatio = FMath::Clamp(TargetArmRatio + ZoomInput * 0.1, 0, 1);
		CurrentArmRatio = FMath::FInterpTo(CurrentArmRatio, TargetArmRatio, DeltaTime, ZoomScale * 5);

		const auto CurrentArmLength = FMath::GetMappedRangeValueClamped(FVector2f(1, 0), ArmLengthClamp,
		                                                                CurrentArmRatio);

		const auto CameraTransform = FTransform(FVector(-1 * CurrentArmLength, 0, 0)) * (UKismetMathLibrary::TEase(
			LookAtOffset, FTransform::Identity, CurrentArmRatio, EEasingFunc::Linear) * RootTransform);

		CameraPose.SetLocation(CameraTransform.GetLocation());
		CameraPose.SetRotation(CameraTransform.GetRotation().Rotator());
	}
}


FCameraNodeEvaluatorPtr UYabwEagleVisionCameraNode::OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const
{
	return Builder.BuildEvaluator<Yabw::FYabwEagleVisionCameraNodeEvaluator>();
}
