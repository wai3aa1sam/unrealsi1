#pragma once

#include "urs_game_app/common/urs_game_app_common.h"
#include <urs_core/game_framework/ursGameMode.h>

#include "tadGameMode.generated.h"


#if 0
#pragma mark --- AtadGameMode-Decl ---
#endif // 0
#if 1

UCLASS()
class AtadGameMode : public AursGameMode
{
	GENERATED_BODY()
public:
	AtadGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};

#endif