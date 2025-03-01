#pragma once

#include "urs_core/common/urs_core_common.h"

#if WITH_EDITOR

#include <Editor/UnrealEd/Public/EditorViewportClient.h>
#include <Editor/UnrealEd/Public/LevelEditorViewport.h>

#if 0
FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
// Create an instance of your custom viewport client
TSharedPtr<FCustomViewportClient> CustomViewportClient = MakeShareable(new FCustomViewportClient());
#endif // 0


#if 0
#pragma mark --- ursLevelEditorViewportClient-Decl ---
#endif // 0
#if 1

struct URS_CORE_API FursLevelEditorViewportClient : public FLevelEditorViewportClient
{
public:

};

#endif

#endif