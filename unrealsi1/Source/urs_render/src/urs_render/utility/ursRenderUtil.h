#pragma once

#include "urs_render/common/urs_render_common.h"

class UStaticMesh;
class FRHICommandList;

#if 0
#pragma mark --- ursRenderUtil-Decl ---
#endif // 0
#if 1

struct URS_RENDER_API ursRenderUtil
{
public:
	static void drawStaticMesh(FRHICommandList& rhiCmdList, UStaticMesh* mesh, uint32 instanceCount);

public:
	static FRHIBlendState* getBlendStateRhi(EBlendMode blendMode);
};

#endif