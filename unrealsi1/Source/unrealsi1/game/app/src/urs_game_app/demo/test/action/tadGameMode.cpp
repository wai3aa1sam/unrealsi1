#include "tadGameMode.h"

#include "tadPlayerController.h"
#include "tadCharacter.h"

#if 0
#pragma mark --- AtadGameMode-Impl ---
#endif // 0
#if 1

AtadGameMode::AtadGameMode()
{
	PlayerControllerClass = AtadPlayerController::StaticClass();
	DefaultPawnClass      = AtadCharacter::StaticClass();

	{
		static ConstructorHelpers::FClassFinder<APawn> v = TEXT("/Script/Engine.Blueprint'/Game/demo/char/prg_greystone/prgGreystone_Bp'");
		DefaultPawnClass = v.Class;
	}
}

void 
AtadGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	/*static ConstructorHelpers::FClassFinder<APawn> playerPawnBpCls(TEXT("/Script/Engine.AnimBlueprint'/Game/Imported/Paragon/ParagonSunWukong/Characters/Heroes/Wukong/SunWukong_AnimBlueprint'"));
	if (playerPawnBpCls.Class)
		URS_LOG("Found");
	else
		URS_LOG("not Found");*/
}

#endif