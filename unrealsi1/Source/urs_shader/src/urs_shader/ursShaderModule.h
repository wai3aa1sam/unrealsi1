// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "urs_shader/common/urs_shader_common.h"
#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

class FursShaderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
