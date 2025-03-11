
#include "ursTransformUtil.h"

#if WITH_EDITOR
#include <Editor/UnrealEd/Public/EditorViewportClient.h>
#include <Editor/UnrealEd/Public/LevelEditorViewport.h>
#endif // WITH_EDITOR

#if 0
#pragma mark --- ursTransformUtil-Impl ---
#endif // 0
#if 1

#if WITH_EDITOR

void 
ursTransformUtil::deprojectScreenToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir, const FIntPoint& screenPos, FEditorViewportClient* client)
{
	FSceneViewFamily viewFamily = FSceneViewFamily::ConstructionValues(client->Viewport, client->GetScene(), client->EngineShowFlags);
	FSceneView* culScene = client->CalcSceneView(&viewFamily);

	culScene->DeprojectFVector2D(screenPos, outWorldPos, outWorldDir);
}

bool 
ursTransformUtil::deprojectScreenToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir, const FIntPoint& screenPos)
{
	//auto* client = static_cast<FEditorViewportClient*>(GEditor->GetActiveViewport()->GetClient());
	auto* client = GLastKeyLevelEditingViewportClient;
	if (!client)
		return false;

	deprojectScreenToWorld_EditorViewport(outWorldPos, outWorldDir, screenPos, client);
	return true;
}

bool 
ursTransformUtil::deprojectMousePosToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir)
{
	//auto* client = Cast<FEditorViewportClient>(GEditor->GetActiveViewport()->GetClient());
	auto* client = GLastKeyLevelEditingViewportClient;
	if (!client)
		return false;

	FIntPoint mousePos;
	mousePos.X = client->GetCachedMouseX();
	mousePos.Y = client->GetCachedMouseY();

	deprojectScreenToWorld_EditorViewport(outWorldPos, outWorldDir, mousePos, client);
	return true;
}

#else

void 
ursTransformUtil::deprojectScreenToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir, const FIntPoint& screenPos, FEditorViewportClient* client)
{

}

bool 
ursTransformUtil::deprojectScreenToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir, const FIntPoint& screenPos)
{
	return false;
}

bool 
ursTransformUtil::deprojectMousePosToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir)
{
	return false;
}

#endif // 0



#endif



