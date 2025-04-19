// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CameraNode.h"
#include "Core/CameraParameterReader.h"
#include "Core/CameraParameters.h"
#include "YabwEagleVisionCameraNode.generated.h"

/**
 * 
 */
UCLASS(meta=(CameraNodeCategories = "Eagle"), DisplayName = "Eagle Vision View (Yabw)")
class YABW_API UYabwEagleVisionCameraNode : public UCameraNode
{
	GENERATED_BODY()

protected:
	virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;

public:
	UPROPERTY(EditAnywhere, Category="Eagle")
	FFloatCameraParameter PitchInput;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FFloatCameraParameter YawInput;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FFloatCameraParameter ZoomInput;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FFloatCameraParameter PitchSpeed;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FFloatCameraParameter YawSpeed;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FFloatCameraParameter ZoomSpeed;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FVector2fCameraParameter PitchAngleClamp;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FVector2fCameraParameter ArmLengthClamp;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FTransform3dCameraParameter InitialRootOffset;

	UPROPERTY(EditAnywhere, Category="Eagle")
	FTransform3dCameraParameter InitialLookAtOffset;
};

namespace Yabw
{
	class FYabwEagleVisionCameraNodeEvaluator final : public UE::Cameras::FCameraNodeEvaluator
	{
		UE_DECLARE_CAMERA_NODE_EVALUATOR(YABW_API, FYabwEagleVisionCameraNodeEvaluator)

	protected:
		virtual void OnInitialize(const UE::Cameras::FCameraNodeEvaluatorInitializeParams& Params,
		                          UE::Cameras::FCameraNodeEvaluationResult& OutResult) override;
		virtual void OnRun(const UE::Cameras::FCameraNodeEvaluationParams& Params,
		                   UE::Cameras::FCameraNodeEvaluationResult& OutResult) override;

	private:
		UE::Cameras::TCameraParameterReader<float> YawInputReader;
		UE::Cameras::TCameraParameterReader<float> YawScaleReader;
		UE::Cameras::TCameraParameterReader<float> PitchInputReader;
		UE::Cameras::TCameraParameterReader<float> PitchScaleReader;
		UE::Cameras::TCameraParameterReader<float> ZoomInputReader;
		UE::Cameras::TCameraParameterReader<float> ZoomScaleReader;
		UE::Cameras::TCameraParameterReader<FVector2f> PitchAngleClampReader;
		UE::Cameras::TCameraParameterReader<FVector2f> ArmLengthClampReader;
		
		float TargetArmRatio = 0.f;
		float CurrentArmRatio = 0.f;

		FTransform RootOffset;
		FTransform LookAtOffset;
	};
}
