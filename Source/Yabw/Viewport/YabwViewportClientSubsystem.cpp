// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppUE4BlueprintCallableFunctionMayBeStatic

#include "YabwViewportClientSubsystem.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include "WinUser.h"
#endif

void UYabwViewportClientSubsystem::EnableLockCursorPosition()
{
	if (bCursorPositionLocked)
	{
		return;
	}

	const auto PlatformApplication = GetApplication();

	if (!PlatformApplication)
	{
		return;;
	}

	const auto CurrentPosition = GetOsCursorPosition();
	CachedPlatformCursorPosition.X = CurrentPosition.X;
	CachedPlatformCursorPosition.Y = CurrentPosition.Y;

	PreviousClipRect = GetOsClipCursor();

	const auto& NativeWindow = this->GetLocalPlayer()->GetGameInstance()->GetGameViewportClient()->GetWindow()->
	                                 GetNativeWindow();

	// Only UseHighPrecisionMouseMode while Locking Cursor
	PlatformApplication->SetHighPrecisionMouseMode(true, NativeWindow);
	TryOsClipCursor(CurrentPosition.X - 1, CurrentPosition.Y - 1, CurrentPosition.X, CurrentPosition.Y);

	FVector2D GameMousePosition = {};
	this->GetLocalPlayer()->GetGameInstance()->GetGameViewportClient()->GetMousePosition(GameMousePosition);
	CachedGameCursorPosition.X = GameMousePosition.X;
	CachedGameCursorPosition.Y = GameMousePosition.Y;

	bCursorPositionLocked = true;
}

void UYabwViewportClientSubsystem::DisableLockCursorPosition()
{
	if (!bCursorPositionLocked)
	{
		return;
	}

	const auto PlatformApplication = GetApplication();

	if (!PlatformApplication)
	{
		return;;
	}


	TryOsClipCursor(PreviousClipRect.X, PreviousClipRect.Y, PreviousClipRect.Z, PreviousClipRect.W);

	const auto& NativeWindow = this->GetLocalPlayer()->GetGameInstance()->GetGameViewportClient()->GetWindow()->
	                                 GetNativeWindow();
	PlatformApplication->SetHighPrecisionMouseMode(false, NativeWindow);

	PreviousClipRect = FVector4f::Zero();
	bCursorPositionLocked = false;
}

void UYabwViewportClientSubsystem::TryOsClipCursor(const int32 Left, const int32 Top, const int32 Right,
                                                   const int32 Bottom)
{
#if PLATFORM_WINDOWS
	const RECT Rect = {Left, Top, Right, Bottom};
	ClipCursor(&Rect);
#endif
}

FVector4f UYabwViewportClientSubsystem::GetOsClipCursor()
{
	RECT Rect;

#if PLATFORM_WINDOWS
	GetClipCursor(&Rect);
#endif

	return FVector4f(Rect.left, Rect.top, Rect.right, Rect.bottom);
}

FVector2f UYabwViewportClientSubsystem::GetOsCursorPosition()
{
	POINT Point;
#if PLATFORM_WINDOWS
	GetCursorPos(&Point);
#endif

	return FVector2f(Point.x, Point.y);
}

GenericApplication* UYabwViewportClientSubsystem::GetApplication()
{
	if (!FSlateApplication::IsInitialized())
	{
		return nullptr;
	}

	return FSlateApplication::Get().GetPlatformApplication().Get();
}
