#include "ursVertexDeclaration.h"

TGlobalResource<FursVertexDeclaration_PosColor> urs_g_vertexDecl_PosColor;

#if 0
#pragma mark --- FursVertexDeclaration_PosColor-Decl ---
#endif // 0
#if 1

FursVertexDeclaration_PosColor::FursVertexDeclaration_PosColor() = default;
FursVertexDeclaration_PosColor::~FursVertexDeclaration_PosColor() = default;

void FursVertexDeclaration_PosColor::InitRHI(FRHICommandListBase& RHICmdList)
{
	FVertexDeclarationElementList Elements;
	uint16 Stride = sizeof(Vertex);
	Elements.Add(FVertexElement(0, STRUCT_OFFSET(Vertex, position), VET_Float4, 0, Stride));
	Elements.Add(FVertexElement(0, STRUCT_OFFSET(Vertex, uv),		VET_Float2, 1, Stride));
	vertexDeclRHI = PipelineStateCache::GetOrCreateVertexDeclaration(Elements);
}

void FursVertexDeclaration_PosColor::ReleaseRHI()
{
	vertexDeclRHI.SafeRelease();
}


#endif