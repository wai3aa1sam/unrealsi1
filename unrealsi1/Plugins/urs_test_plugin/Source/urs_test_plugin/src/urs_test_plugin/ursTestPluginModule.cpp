// Copyright Epic Games, Inc. All Rights Reserved.

#include "ursTestPluginModule.h"
#include <Interfaces/IPluginManager.h>

#define LOCTEXT_NAMESPACE "FursTestPluginModule"

void FursTestPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//TSharedPtr<IPlugin> plugin = IPluginManager::Get().FindPlugin(TEXT(URS_TEST_PLUGIN_NAME_CSTR));
	//FString shaderDir = FPaths::Combine(plugin->GetBaseDir(), TEXT("Shaders"), TEXT(URS_TEST_PLUGIN_NAME_CSTR));

	//AddShaderSourceDirectoryMapping(URS_TEST_PLUGIN_ROOT_CSTR, shaderDir);
}

void FursTestPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
