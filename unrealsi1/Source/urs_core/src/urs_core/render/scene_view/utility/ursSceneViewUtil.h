#pragma once

#include "urs_core/render/common/urs_render_common.h"
#include <Runtime/Renderer/Private/SceneRendering.h>

#if 0
#pragma mark --- ursSceneViewUtil-Decl ---
#endif // 0
#if 1

struct URS_CORE_API ursSceneViewUtil
{
public:
	static const FViewInfo& getViewInfo_Unsafe(const FSceneView& view);
	static FIntRect getRawViewRect_Unsafe(const FSceneView& view);
};

#endif