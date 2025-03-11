// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "urs_render/common/urs_render_common.h"
#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

class FursRenderModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
