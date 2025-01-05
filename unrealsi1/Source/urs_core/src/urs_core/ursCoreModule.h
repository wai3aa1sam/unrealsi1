// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "urs_core/common/urs_core_common.h"
#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

class FursCoreModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
