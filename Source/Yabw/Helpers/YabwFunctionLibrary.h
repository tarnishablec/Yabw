﻿// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "YabwFunctionLibrary.generated.h"

class UGameplayCameraComponent;
class AGameplayCameraSystemActor;

/**
 * 
 */
UCLASS()
class YABW_API UYabwFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, Category="Yabw")
    static void GetEvaluatedCameraView(AGameplayCameraSystemActor* CameraSystemActor, FMinimalViewInfo& DesiredView);
};
