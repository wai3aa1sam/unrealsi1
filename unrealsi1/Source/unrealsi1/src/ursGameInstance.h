#pragma once

#include "common/urs_common.h"
#include <Engine/GameInstance.h>

#include "ursGameInstance.generated.h"

UCLASS()
class UursGameInstance : public UGameInstance 
{
	GENERATED_BODY()
public:
	virtual void OnStart() override;
};