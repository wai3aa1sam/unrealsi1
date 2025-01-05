#include "stcTestPlayerControllerPawn.h"

#include "stcTestComponentActor.h"
#include "stcTestPlayerController.h"

AstcTestPlayerControllerPawn::AstcTestPlayerControllerPawn() 
{
	Cube = ursActorUtil::createDefaultSubObj<UstcCCube>(this, "Cube");
	SetRootComponent(Cube);
}

void AstcTestPlayerControllerPawn::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

}


#if 0
#pragma mark --- UstcTestGameInst-Impl ---
#endif // 0
#if 1

void UstcTestGameInst::OnStart() {
	Super::OnStart();
	URS_LOG("UstcTestGameInst::OnStart()");
}



#endif

#if 0
#pragma mark --- AstcTestGameMode-Impl ---
#endif // 0
#if 1

AstcTestGameMode::AstcTestGameMode() 
{
	PlayerStateClass = nullptr;
	GameStateClass = nullptr;
	SpectatorClass = nullptr;
	HUDClass = nullptr;

	//	PlayerControllerClass = nullptr;
	PlayerControllerClass = AstcTestPlayerController::StaticClass();

	//	DefaultPawnClass = nullptr;
	DefaultPawnClass = AstcTestPlayerControllerPawn::StaticClass();
}

void AstcTestGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);
	URS_LOG("AstcTestGameMode::InitGame()");
}

void AstcTestGameMode::InitGameState() {
	Super::InitGameState();
	URS_LOG("AstcTestGameMode::InitGameState()");
}

void AstcTestGameMode::StartPlay() {
	Super::StartPlay();
	URS_LOG("AstcTestGameMode::StartPlay()");
}


#endif