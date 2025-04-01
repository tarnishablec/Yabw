// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "YabwFunctionLibrary.h"

#include "Core/CameraSystemEvaluator.h"
#include "GameFramework/GameplayCameraSystemActor.h"
#include "GameFramework/GameplayCameraSystemComponent.h"

void UYabwFunctionLibrary::GetEvaluatedCameraView(AGameplayCameraSystemActor* CameraSystemActor,
                                                  FMinimalViewInfo& DesiredView)
{
    // Cause AGameplayCameraSystemActor::GetAutoSpawnedCameraSystemActor is Not Exported , We Need to Pass CameraSystemActor as Parameter
    // const auto CameraSystemActor = AGameplayCameraSystemActor::GetAutoSpawnedCameraSystemActor(PlayerController);

    if (!CameraSystemActor)
    {
        return;
    }

    const auto CameraSystem = CameraSystemActor->GetCameraSystemComponent();

    if (!CameraSystem)
    {
        return;
    }

    const auto Evaluator = CameraSystem->GetCameraSystemEvaluator();
    if (Evaluator.IsValid())
    {
        Evaluator.Get()->GetEvaluatedCameraView(DesiredView);
    }
}

