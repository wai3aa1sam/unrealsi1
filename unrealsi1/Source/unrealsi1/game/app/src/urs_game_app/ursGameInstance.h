#pragma once

#include "urs_game_app/common/urs_game_app_common.h"
#include <Engine/GameInstance.h>

#include "ursGameInstance.generated.h"

UCLASS()
class UursGameInstance : public UGameInstance 
{
	GENERATED_BODY()
public:
	virtual void OnStart() override;
};