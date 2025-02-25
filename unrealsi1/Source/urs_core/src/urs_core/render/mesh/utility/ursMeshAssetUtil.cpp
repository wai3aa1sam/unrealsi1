#include "ursMeshAssetUtil.h"
#include "../../vertex/ursVertexDeclaration.h"

#if 0
#pragma mark --- ursMeshAssetUtil-Impl ---
#endif // 0
#if 1

FBufferRHIRef 
ursMeshAssetUtil::createQuadVertexBuffer(FRHICommandListBase& rhiCmdList, bool isTriangleList, float ULeft, float URight, float VTop, float VBottom)
{
	// TGlobalResource<FClearVertexBuffer> GClearVertexBuffer;
	FRHIResourceCreateInfo CreateInfo(TEXT("quad_vtxBuf"));
	FBufferRHIRef VertexBufferRHI = rhiCmdList.CreateVertexBuffer(sizeof(FursVertex_PosColor) * 6, BUF_Volatile, CreateInfo);
	void* VoidPtr = rhiCmdList.LockBuffer(VertexBufferRHI, 0, sizeof(FursVertex_PosColor) * 6, RLM_WriteOnly);

	FursVertex_PosColor* Vertices = (FursVertex_PosColor*)VoidPtr;

	// y is up, z is forward, unlike unreal traditional axis
	if (isTriangleList)
	{
		Vertices[0].position.Set(-1.0f,  1.0f, 1.0, 1.0f); // Top Left
		Vertices[1].position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[2].position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left

		Vertices[3].position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[4].position.Set( 1.0f,	-1.0f, 1.0, 1.0f); // Bottom Right
		Vertices[5].position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left

		Vertices[0].uv.Set(ULeft, VTop);
		Vertices[1].uv.Set(URight, VTop);
		Vertices[2].uv.Set(ULeft, VBottom);

		Vertices[3].uv.Set(URight, VTop);
		Vertices[4].uv.Set(URight, VBottom);
		Vertices[5].uv.Set(ULeft, VBottom);
	}
	else // 
	{
		Vertices[0].position.Set(-1.0f,  1.0f, 1.0, 1.0f); // Top Left
		Vertices[1].position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[2].position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left
		Vertices[3].position.Set( 1.0f,	-1.0f, 1.0, 1.0f); // Bottom Right

		Vertices[0].uv.Set(ULeft, VTop);
		Vertices[1].uv.Set(URight, VTop);
		Vertices[2].uv.Set(ULeft, VBottom);
		Vertices[3].uv.Set(URight, VBottom);
	}

	rhiCmdList.UnlockBuffer(VertexBufferRHI);

	return VertexBufferRHI;
}

FBufferRHIRef 
ursMeshAssetUtil::createQuadIndexBuffer(FRHICommandListBase& rhiCmdList/*, bool isCcw*/)
{
	//static const uint16 Indices[] = { 0, 1, 2, 0, 2, 3 };
	static const uint16 Indices[] = { 0, 2, 1, 1, 2, 3 };

	FRHIResourceCreateInfo CreateInfo(TEXT("quad_idxBuf"));
	FBufferRHIRef IndexBufferRHI = rhiCmdList.CreateIndexBuffer(sizeof(uint16), sizeof(uint16) * 6, BUF_Volatile, CreateInfo);
	void* VoidPtr2 = rhiCmdList.LockBuffer(IndexBufferRHI, 0, sizeof(uint16) * 6, RLM_WriteOnly);
	FPlatformMemory::Memcpy(VoidPtr2, Indices, sizeof(uint16) * 6);
	rhiCmdList.UnlockBuffer(IndexBufferRHI);

	return IndexBufferRHI;
}


#endif