// Copyright Epic Games, Inc. All Rights Reserved.

#include "ursShaderModule.h"
#include <Interfaces/IPluginManager.h>

#define LOCTEXT_NAMESPACE "FursShaderModule"

void FursShaderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(TEXT(URS_SHADER_NAME_CSTR));
	FString shaderDir	= FPaths::Combine(plugin->GetBaseDir(), TEXT("Shaders"), TEXT(URS_SHADER_NAME_CSTR));
	FString materialDir = FPaths::Combine(plugin->GetBaseDir(), TEXT("Shaders"), TEXT(URS_MATERIAL_NAME_CSTR));

	AddShaderSourceDirectoryMapping(URS_SHADER_ROOT_CSTR, shaderDir);
	AddShaderSourceDirectoryMapping(URS_MATERIAL_ROOT_CSTR, materialDir);
}

void FursShaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
