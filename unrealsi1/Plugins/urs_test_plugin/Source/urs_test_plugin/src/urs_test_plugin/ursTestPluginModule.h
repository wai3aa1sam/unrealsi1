// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "urs_test_plugin/common/urs_test_plugin_common.h"
#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

class FursTestPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
