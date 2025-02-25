#pragma once

#include "urs_core/render/common/urs_render_common.h"

#if 0
#pragma mark --- FursVertexDeclaration_PosColor-Decl ---
#endif // 0
#if 1

struct URS_CORE_API FursVertex_PosColor
{
public:
	FVector4f position;
	FVector2f uv;

public:
	FursVertex_PosColor() { }

	FursVertex_PosColor(const FVector4f& pos, const FVector2f& uv_)
		: position(pos)
		, uv(uv_)
	{ }
};

class URS_CORE_API FursVertexDeclaration_PosColor : public FRenderResource
{
public:
	using Vertex = FursVertex_PosColor;

public:
	FVertexDeclarationRHIRef vertexDeclRHI;

public:
	FursVertexDeclaration_PosColor();
	virtual ~FursVertexDeclaration_PosColor();

public:
	virtual void InitRHI(FRHICommandListBase& RHICmdList) override;
	virtual void ReleaseRHI() override;
};
URS_CORE_API extern TGlobalResource<FursVertexDeclaration_PosColor> urs_g_vertexDecl_PosColor;

#endif