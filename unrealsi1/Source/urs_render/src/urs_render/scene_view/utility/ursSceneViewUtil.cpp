#include "ursSceneViewUtil.h"


#if 0
#pragma mark --- ursSceneViewUtil-Impl ---
#endif // 0
#if 1

const FViewInfo& 
ursSceneViewUtil::getViewInfo_Unsafe(const FSceneView& view)
{
	check(view.bIsViewInfo);
	return static_cast<const FViewInfo&>(view);
}

FIntRect 
ursSceneViewUtil::getRawViewRect_Unsafe(const FSceneView& view)
{
	return getViewInfo_Unsafe(view).ViewRect;
}

#endif