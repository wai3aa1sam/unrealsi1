#include "ursGameAppModule.h"
#include "Interfaces/IPluginManager.h"

void
FursGameAppModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	//FString shaderRoot = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"), TEXT(URS_SHADER_NAME_CSTR));
	//AddShaderSourceDirectoryMapping(URS_SHADER_ROOT_CSTR, shaderRoot);
}

void 
FursGameAppModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}
