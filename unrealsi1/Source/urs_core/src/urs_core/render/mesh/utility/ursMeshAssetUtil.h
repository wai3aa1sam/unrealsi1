#pragma once

#include "urs_core/render/common/urs_render_common.h"

class FRHICommandListBase;

#if 0
#pragma mark --- ursMeshAssetUtil-Decl ---
#endif // 0
#if 1

struct URS_CORE_API ursMeshAssetUtil
{
public:
	static FBufferRHIRef createQuadVertexBuffer(FRHICommandListBase& rhiCmdList, bool isTriangleList = true, float ULeft = 0.0f, float URight = 1.0f, float VTop = 0.0f, float VBottom = 1.0f);
	static FBufferRHIRef createQuadIndexBuffer(FRHICommandListBase& rhiCmdList/*, bool isCcw*/);
};



#endif