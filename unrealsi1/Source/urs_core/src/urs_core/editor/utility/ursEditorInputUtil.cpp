#include "ursEditorInputUtil.h"

#if WITH_EDITOR
#include <Editor/UnrealEd/Public/Editor.h>
#include <Editor/UnrealEd/Public/LevelEditorViewport.h>

#if 0
#pragma mark --- ursEditorInputUtil-Impl ---
#endif // 0
#if 1

bool 
ursEditorInputUtil::isKeyPressed(const FKey& key)
{
	return GLastKeyLevelEditingViewportClient && GLastKeyLevelEditingViewportClient->Viewport->KeyState(key);
}

#endif

#endif

