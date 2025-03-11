// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

/*
* references:
* ~ https://dev.epicgames.com/documentation/en-us/unreal-engine/creating-a-new-global-shader-as-a-plugin-in-unreal-engine
*/

#include "tldLensDistortionBlueprintLibrary.h"

ULensDistortionBlueprintLibrary::ULensDistortionBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{ }

// static
void ULensDistortionBlueprintLibrary::GetUndistortOverscanFactor(
    const FFooCameraModel& CameraModel,
    float DistortedHorizontalFOV,
    float DistortedAspectRatio,
    float& UndistortOverscanFactor)
{
    UndistortOverscanFactor = CameraModel.GetUndistortOverscanFactor(DistortedHorizontalFOV, DistortedAspectRatio);
}

// static
void ULensDistortionBlueprintLibrary::DrawUVDisplacementToRenderTarget(
    const UObject* WorldContextObject,
    const FFooCameraModel& CameraModel,
    float DistortedHorizontalFOV,
    float DistortedAspectRatio,
    float UndistortOverscanFactor,
    class UTextureRenderTarget2D* OutputRenderTarget,
    float OutputMultiply,
    float OutputAdd)
{
    CameraModel.DrawUVDisplacementToRenderTarget(
        WorldContextObject->GetWorld(),
        DistortedHorizontalFOV, DistortedAspectRatio,
        UndistortOverscanFactor, OutputRenderTarget,
        OutputMultiply, OutputAdd);
}
