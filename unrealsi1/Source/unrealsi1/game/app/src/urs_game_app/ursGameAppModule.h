#pragma once

#include "urs_game_app/common/urs_game_app_common.h"

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>


class FursGameAppModule : public FDefaultGameModuleImpl
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
