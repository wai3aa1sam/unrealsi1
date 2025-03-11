#pragma once

#include "urs_core/common/urs_core_common.h"

class FEditorViewportClient;

#if 0
#pragma mark --- ursTransformUtil-Decl ---
#endif // 0
#if 1

struct URS_CORE_API ursTransformUtil
{
public:
    static void deprojectScreenToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir, const FIntPoint& screenPos, FEditorViewportClient* client);
    static bool deprojectScreenToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir, const FIntPoint& screenPos);
    static bool deprojectMousePosToWorld_EditorViewport(FVector& outWorldPos, FVector& outWorldDir);
};

#endif