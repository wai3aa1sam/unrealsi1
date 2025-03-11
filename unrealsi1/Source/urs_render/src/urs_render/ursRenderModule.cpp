// Copyright Epic Games, Inc. All Rights Reserved.

#include "ursRenderModule.h"
#include <Interfaces/IPluginManager.h>

#define LOCTEXT_NAMESPACE "FursRenderModule"

void FursRenderModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(TEXT(URS_RENDER_NAME_CSTR));
	FString rootDir = FPaths::ProjectDir();
	FString shaderDir	= FPaths::Combine(rootDir, TEXT("Shaders"), TEXT(URS_RENDER_NAME_CSTR));
	//FString materialDir = FPaths::Combine(rootDir, TEXT("Shaders"), TEXT(URS_MATERIAL_NAME_CSTR));

	AddShaderSourceDirectoryMapping(URS_RENDER_ROOT_CSTR, shaderDir);
	AddShaderSourceDirectoryMapping("/urs_shader", shaderDir);
	//AddShaderSourceDirectoryMapping(URS_MATERIAL_ROOT_CSTR, materialDir);
}

void FursRenderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
