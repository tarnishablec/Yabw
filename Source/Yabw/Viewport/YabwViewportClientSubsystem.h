// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "YabwViewportClientSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class YABW_API UYabwViewportClientSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void EnableLockCursorPosition();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void DisableLockCursorPosition();

	UFUNCTION(BlueprintCallable, BlueprintCosmetic)
	void TryOsClipCursor(const int32 Left, const int32 Top, const int32 Right, const int32 Bottom);

	UFUNCTION(BlueprintPure, BlueprintCosmetic)
	FVector4f GetOsClipCursor();

	UFUNCTION(BlueprintPure, BlueprintCosmetic)
	FVector2f GetOsCursorPosition();

	GenericApplication* GetApplication();

protected:
	bool bCursorPositionLocked = false;

	FVector2f CachedPlatformCursorPosition;
	FVector2f CachedGameCursorPosition;

	FVector4f PreviousClipRect;
};
