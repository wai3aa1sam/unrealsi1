#include "ursInputUtil.h"
#include "urs_core/editor/utility/ursEditorInputUtil.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

#if 0
#pragma mark --- ursInputUtil-Impl ---
#endif // 0
#if 1

bool 
ursInputUtil::isKeyPressed(const FKey& key, APlayerController* playerController)
{
	#if WITH_EDITOR
	return ursEditorInputUtil::isKeyPressed(key) || (playerController && playerController->IsInputKeyDown(key));
	#else
	return playerController->IsInputKeyDown(key);
	#endif // WITH_EIDTOR
}

bool
ursInputUtil::isKeyPressed(const FKey& key, UWorld* world, int32 playerIndex)
{
	auto* playerCtrl = UGameplayStatics::GetPlayerController(world, playerIndex);
	return isKeyPressed(key, playerCtrl);
}

#endif

