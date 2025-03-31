// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/CameraNode.h"
#include "Core/CameraParameters.h"
#include "YabwEagleVisionCameraNode.generated.h"

/**
 * 
 */
UCLASS(meta=(CameraNodeCategories = "Eagle"), DisplayName = "Eagle Vision (Yabw)")
class YABW_API UYabwEagleVisionCameraNode : public UCameraNode
{
    GENERATED_BODY()

protected:
    virtual FCameraNodeEvaluatorPtr OnBuildEvaluator(FCameraNodeEvaluatorBuilder& Builder) const override;

public:
    UPROPERTY(EditAnywhere, Category="Eagle")
    FFloatCameraParameter YawInput;

    UPROPERTY(EditAnywhere, Category="Eagle")
    FFloatCameraParameter PitchInput;

    UPROPERTY(EditAnywhere, Category="Eagle")
    FFloatCameraParameter ZoomInput;

    UPROPERTY(EditAnywhere, Category="Eagle")
    FFloatCameraParameter YawSpeed;

    UPROPERTY(EditAnywhere, Category="Eagle")
    FFloatCameraParameter PitchSpeed;

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
