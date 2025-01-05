#pragma once

#include "urs_tutorial/common/urs_tutorial_common.h"

#include "Engine/GameInstance.h"
#include "GameFramework/GameModeBase.h"

#include "stcTestPlayerControllerPawn.generated.h"

class UstcCCube;

UCLASS()
class UNREALSI1_API AstcTestPlayerControllerPawn : public APawn 
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere) UstcCCube* Cube;

	AstcTestPlayerControllerPawn();

	virtual void Tick(float DeltaSeconds) override;
};


#if 0
#pragma mark --- UstcTestGameInst-Decl ---
#endif // 0
#if 1


UCLASS()
class UstcTestGameInst : public UGameInstance {
	GENERATED_BODY()
public:
	virtual void OnStart() override;
};

#endif

#if 0
#pragma mark --- AstcTestGameMode-Decl ---
#endif // 0
#if 1


UCLASS()
class AstcTestGameMode : public AGameModeBase 
{
	GENERATED_BODY()
public:

	AstcTestGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() override;

	virtual void StartPlay() override;

};

#endif // 1
