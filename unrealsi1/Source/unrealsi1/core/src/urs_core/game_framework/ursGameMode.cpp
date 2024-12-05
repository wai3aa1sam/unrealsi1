#include "ursGameMode.h"

#include "ursPlayerController.h"

#include <DynamicResolutionState.h>
#include <Gameframework/GameUserSettings.h>

#if 0
#pragma mark --- AursGameMode-Impl ---
#endif // 0
#if 1

AursGameMode::AursGameMode()
{
    #if 0
    PlayerControllerClass = AursPlayerController::StaticClass();
	DefaultPawnClass      = AursCharacter::StaticClass();

	{
		static ConstructorHelpers::FClassFinder<APawn> v = TEXT("/Script/Engine.Blueprint'/Game/demo/char/prg_greystone/prgGreystone_Bp'");
		DefaultPawnClass = v.Class;
	}
    #endif
}

void 
AursGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	/*static ConstructorHelpers::FClassFinder<APawn> playerPawnBpCls(TEXT("/Script/Engine.AnimBlueprint'/Game/Imported/Paragon/ParagonSunWukong/Characters/Heroes/Wukong/SunWukong_AnimBlueprint'"));
	if (playerPawnBpCls.Class)
		URS_LOG("Found");
	else
		URS_LOG("not Found");*/

}

#endif