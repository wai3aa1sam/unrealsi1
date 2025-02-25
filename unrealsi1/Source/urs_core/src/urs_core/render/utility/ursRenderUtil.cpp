#include "ursRenderUtil.h"

#include <Runtime/Renderer/Private/SceneRendering.h>
#include <MeshPassProcessor.h>
#include <SceneView.h>

#include <Runtime/Renderer/Public/FXRenderingUtils.h>

#if 0
#pragma mark --- ursRenderUtil-Impl ---
#endif // 0
#if 1

void 
ursRenderUtil::drawStaticMesh(FRHICommandList& rhiCmdList, UStaticMesh* mesh, uint32 instanceCount)
{
	URS_ASSERT(false, "not yet supported");
	//GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= mesh->GetRenderData()->LODVertexFactories[0].VertexFactory.GetDeclaration();

	auto* rdData = mesh->GetRenderData();
	auto& idxBuf = rdData->LODResources[0].IndexBuffer;

	FMeshDrawCommand cmd;
	rdData->LODVertexFactories[0].VertexFactory.GetStreams(GMaxRHIFeatureLevel, EVertexInputStreamType::Default, cmd.VertexStreams);
	cmd.IndexBuffer = idxBuf.IndexBufferRHI;

	//const int8 PrimitiveIdStreamIndex = (IsUniformBufferStaticSlotValid(SceneArgs.BatchedPrimitiveSlot) ? -1 : MeshDrawCommand.PrimitiveIdStreamIndex);
	for (int32 VertexBindingIndex = 0; VertexBindingIndex < cmd.VertexStreams.Num(); VertexBindingIndex++)
	{
		const FVertexInputStream& Stream = cmd.VertexStreams[VertexBindingIndex];
		rhiCmdList.SetStreamSource(Stream.StreamIndex, Stream.VertexBuffer, Stream.Offset);
		//StateCache.VertexStreams[Stream.StreamIndex] = Stream;
	}
	//MeshDrawCommand.ShaderBindings.SetOnCommandList(RHICmdList, MeshPipelineState.BoundShaderState.AsBoundShaderState(), StateCache.ShaderBindings);

	auto vtxCount = rdData->LODResources[0].GetNumVertices();
	auto primitiveCount = vtxCount / 3;
	auto instCount = instanceCount;
	rhiCmdList.DrawIndexedPrimitive(cmd.IndexBuffer, 0, 0, vtxCount, 0, primitiveCount, instCount);
}

/*
* copy from void FSlateMaterialShaderPS::SetBlendState(FGraphicsPipelineStateInitializer& GraphicsPSOInit, const FMaterial* Material)
*/
FRHIBlendState* 
ursRenderUtil::getBlendStateRhi(EBlendMode blendMode)
{
	switch (blendMode)
	{
		case BLEND_Opaque:				{ return TStaticBlendState<>::GetRHI(); } break;
		case BLEND_Masked:				{ return TStaticBlendState<>::GetRHI(); } break;
		case BLEND_Translucent:			{ return TStaticBlendState<CW_RGBA, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add, BF_InverseDestAlpha, BF_One>::GetRHI(); } break;
		case BLEND_Additive:			{ return TStaticBlendState<CW_RGBA, BO_Add, BF_One, BF_One, BO_Add, BF_One, BF_One>::GetRHI(); } break;
		case BLEND_Modulate:			{ return TStaticBlendState<CW_RGB, BO_Add, BF_Zero, BF_SourceColor>::GetRHI(); } break;
		case BLEND_AlphaComposite:		{ return TStaticBlendState<CW_RGBA, BO_Add, BF_One, BF_InverseSourceAlpha, BO_Add, BF_One, BF_InverseSourceAlpha>::GetRHI(); } break;
		case BLEND_AlphaHoldout:		{ return TStaticBlendState<CW_RGBA, BO_Add, BF_Zero, BF_InverseSourceAlpha, BO_Add, BF_Zero, BF_InverseSourceAlpha>::GetRHI(); } break;
		default: { URS_ASSERT(false, "not found"); }
	};
	return TStaticBlendState<>::GetRHI();
}



#endif