#pragma once

#include "urs_core/common/urs_core_common.h"


#if 0
#pragma mark --- ursPhysicsUtil-Decl ---
#endif // 0
#if 1

struct URS_CORE_API ursPhysicsUtil
{
public:
	static bool lineTraceByMousePos(FHitResult& outHit, UWorld* world, int32 playerIndex = 0);
	static bool lineTraceByMousePos_Editor(FHitResult& outHit, UWorld* world);
};

#endif