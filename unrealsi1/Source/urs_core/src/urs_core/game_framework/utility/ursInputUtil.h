#pragma once

#include "urs_core/common/urs_core_common.h"

class UWorld;
class APlayerController;

#if 0
#pragma mark --- ursInputUtil-Decl ---
#endif // 0
#if 1

struct URS_CORE_API ursInputUtil
{
public:
	static bool isKeyPressed(const FKey& key, APlayerController* playerController);
	static bool isKeyPressed(const FKey& key, UWorld* world, int32 playerIndex = 0);

};

#endif