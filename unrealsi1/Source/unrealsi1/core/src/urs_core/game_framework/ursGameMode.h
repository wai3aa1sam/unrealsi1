#pragma once

#include "common/urs_common.h"

#include <GameFramework/GameModeBase.h>

#include "ursGameMode.generated.h"


#if 0
#pragma mark --- AursGameMode-Decl ---
#endif // 0
#if 1

UCLASS()
class AursGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AursGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};

#endif