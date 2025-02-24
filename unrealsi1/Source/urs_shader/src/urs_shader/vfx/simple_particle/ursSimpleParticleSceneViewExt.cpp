#include "ursSimpleParticleSceneViewExt.h"

#include "ursSimpleParticle.h"
#include "ursSimpleParticle_Shaders.h"
#include <MediaShaders.h>		// use a workaround to get the FMediaElementVertex struct

FBufferRHIRef
createQuadVertexBuffer(FRHICommandListBase& rhiCmdList, bool isTriangleList = true, float ULeft = 0.0f, float URight = 1.0f, float VTop = 0.0f, float VBottom = 1.0f)
{
	// TGlobalResource<FClearVertexBuffer> GClearVertexBuffer;
	FRHIResourceCreateInfo CreateInfo(TEXT("quad_vtxBuf"));
	FBufferRHIRef VertexBufferRHI = rhiCmdList.CreateVertexBuffer(sizeof(FMediaElementVertex) * 6, BUF_Volatile, CreateInfo);
	void* VoidPtr = rhiCmdList.LockBuffer(VertexBufferRHI, 0, sizeof(FMediaElementVertex) * 6, RLM_WriteOnly);

	FMediaElementVertex* Vertices = (FMediaElementVertex*)VoidPtr;

	// y is up, z is forward, unlike unreal traditional axis
	if (isTriangleList)
	{
		Vertices[0].Position.Set(-1.0f,  1.0f, 1.0, 1.0f); // Top Left
		Vertices[1].Position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[2].Position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left

		Vertices[3].Position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[4].Position.Set( 1.0f,	-1.0f, 1.0, 1.0f); // Bottom Right
		Vertices[5].Position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left

		Vertices[0].TextureCoordinate.Set(ULeft, VTop);
		Vertices[1].TextureCoordinate.Set(URight, VTop);
		Vertices[2].TextureCoordinate.Set(ULeft, VBottom);

		Vertices[3].TextureCoordinate.Set(URight, VTop);
		Vertices[4].TextureCoordinate.Set(URight, VBottom);
		Vertices[5].TextureCoordinate.Set(ULeft, VBottom);
	}
	else // 
	{
		Vertices[0].Position.Set(-1.0f,  1.0f, 1.0, 1.0f); // Top Left
		Vertices[1].Position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[2].Position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left
		Vertices[3].Position.Set( 1.0f,	-1.0f, 1.0, 1.0f); // Bottom Right

		Vertices[0].TextureCoordinate.Set(ULeft, VTop);
		Vertices[1].TextureCoordinate.Set(URight, VTop);
		Vertices[2].TextureCoordinate.Set(ULeft, VBottom);
		Vertices[3].TextureCoordinate.Set(URight, VBottom);
	}
	

	rhiCmdList.UnlockBuffer(VertexBufferRHI);

	return VertexBufferRHI;
}

FBufferRHIRef 
createQuadIndexBuffer(FRHICommandListBase& rhiCmdList/*, bool isCcw*/)
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

struct ursRenderUtil		// should change to ursSceneViewUtil
{
public:
	static const FViewInfo& getViewInfo_Unsafe(const FSceneView& view)
	{
		check(view.bIsViewInfo);
		return static_cast<const FViewInfo&>(view);
	}

	static FIntRect getRawViewRect_Unsafe(const FSceneView& view)
	{
		return getViewInfo_Unsafe(view).ViewRect;
	}

};


#if 0
#pragma mark --- FursSimpleParticleSceneViewExt-Impl ---
#endif // 0
#if 1

FursSimpleParticleSceneViewExt::FursSimpleParticleSceneViewExt(const FAutoRegister& autoReg, AursSimpleParticle* simpleParticle)
	: Super(autoReg)
{
	_simpleParticle = simpleParticle;
}

FursSimpleParticleSceneViewExt::~FursSimpleParticleSceneViewExt()
{
}

void 
FursSimpleParticleSceneViewExt::requestExecute(const FursSimpleParticleConfigs& configs)
{
	_passParams.configs = configs;
}

void 
FursSimpleParticleSceneViewExt::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	Super::_SetupViewFamily(InViewFamily);

}

void 
FursSimpleParticleSceneViewExt::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	Super::_SetupView(InViewFamily, InView);

}

void
FursSimpleParticleSceneViewExt::SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InViewInfo)
{
	Super::SetupViewPoint(Player, InViewInfo);

}

void
FursSimpleParticleSceneViewExt::SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData)
{
	Super::SetupViewProjectionMatrix(InOutProjectionData);

}

void
FursSimpleParticleSceneViewExt::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	Super::_BeginRenderViewFamily(InViewFamily);

}

void
FursSimpleParticleSceneViewExt::PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	Super::PreRenderViewFamily_RenderThread(GraphBuilder, InViewFamily);

}

void 
FursSimpleParticleSceneViewExt::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	Super::PreRenderView_RenderThread(GraphBuilder, InView);

}

void
FursSimpleParticleSceneViewExt::PreInitViews_RenderThread(FRDGBuilder& GraphBuilder)
{
	Super::PreInitViews_RenderThread(GraphBuilder);

}

//void 
//FursSimpleParticleSceneViewExt::PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated)
//{
//	Super::PreRenderBasePass_RenderThread(GraphBuilder, bDepthBufferIsPopulated);
//
//}

void
FursSimpleParticleSceneViewExt::PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures)
{
	Super::PostRenderBasePassDeferred_RenderThread(GraphBuilder, InView, RenderTargets, SceneTextures);

}

void 
FursSimpleParticleSceneViewExt::PostRenderBasePassMobile_RenderThread(FRHICommandList& RHICmdList, FSceneView& InView)
{
	Super::PostRenderBasePassMobile_RenderThread(RHICmdList, InView);

}

void
FursSimpleParticleSceneViewExt::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	Super::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);
	
	check(IsInRenderingThread());

	if (!_passParams.configs.isValid())
		return;

	_passParams.sceneView = &View;

	/*bool isInvalidMesh = !_mesh || !_mesh->GetRenderData() || _mesh->GetRenderData()->LODResources.IsEmpty();
	if (isInvalidMesh)
		return;*/

	auto& rdgBuilder = GraphBuilder;
	addSimulateParticlePass(rdgBuilder, &_passParams);
	addRenderParticlePass(rdgBuilder,	&_passParams);
}

void
FursSimpleParticleSceneViewExt::SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
{
	Super::SubscribeToPostProcessingPass(Pass, InOutPassCallbacks, bIsPassEnabled);

}

void
FursSimpleParticleSceneViewExt::PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	Super::PostRenderViewFamily_RenderThread(GraphBuilder, InViewFamily);

}

void 
FursSimpleParticleSceneViewExt::PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	Super::PostRenderView_RenderThread(GraphBuilder, InView);

}

void 
FursSimpleParticleSceneViewExt::addSimulateParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams)
{
	//RDG_CSV_STAT_EXCLUSIVE_SCOPE(GraphBuilder, RenderBasePass);
	//SCOPED_NAMED_EVENT(FDeferredShadingSceneRenderer_RenderBasePass, FColor::Emerald);

	const auto& configs = passParams->configs;

	if (!configs.isValid())
		return;

	TShaderMapRef<FursSimpleParticle_CS> cs(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	auto* params = rdgBuilder.AllocParameters<FursSimpleParticle_CS::FParameters>();	// 
	cs->setupShaderParams(params, rdgBuilder, _passParams);
	FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("simpPtcSimulateParticlePass"), cs, params, FIntVector(configs.getThreadGroup(), 1, 1));
}

void 
FursSimpleParticleSceneViewExt::addRenderParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams)
{
	auto& rhiCmdList	= rdgBuilder.RHICmdList;
	auto& sceneView		= *passParams->sceneView;
	auto& rdgRscsRef	= passParams->rdgRscsRef;
	const auto& configs	= passParams->configs;

	if (!rdgRscsRef.particlePositionBuffer)
		return;

	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_BasePass));
	//RenderBasePassInternal(GraphBuilder, InViews, SceneTextures, BasePassRenderTargets, BasePassDepthStencilAccess, ForwardBasePassTextures, DBufferTextures, bDoParallelBasePass, bRenderLightmapDensity, InstanceCullingManager, bNaniteEnabled, NaniteBasePassShadingCommands, NaniteRasterResults);
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_AfterBasePass));

	// if (SubmitDrawBegin(MeshDrawCommand, GraphicsMinimalPipelineStateSet, SceneArgs, InstanceFactor, RHICmdList, StateCache, bAllowSkipDrawCommand))
	// AddSimpleMeshPass(

	#if 1
	FGlobalShaderMap* shaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FursSimpleParticle_VS> vs{shaderMap};
	TShaderMapRef<FursSimpleParticle_PS> ps{shaderMap};

	auto* shaderParams = rdgBuilder.AllocParameters<FursSimpleParticle_PS::FParameters>();

	auto& viewInfo = ursRenderUtil::getViewInfo_Unsafe(sceneView);

	auto sceneTexs = viewInfo.GetSceneTextures();
	shaderParams->RenderTargets[0]				= FRenderTargetBinding(sceneTexs.Color.Target, ERenderTargetLoadAction::ELoad);
	shaderParams->RenderTargets.DepthStencil	= FDepthStencilBinding(sceneTexs.Depth.Target, ERenderTargetLoadAction::ELoad, FExclusiveDepthStencil::DepthWrite_StencilNop);

	shaderParams->View							= viewInfo.ViewUniformBuffer;
	shaderParams->m_color						= passParams->configs.color;
	shaderParams->m_scale						= passParams->configs.scale;
	shaderParams->m_matrixView					= FMatrix44f{viewInfo.ViewMatrices.GetViewMatrix()};
	shaderParams->m_objPos						= passParams->configs.emitPosition;		// TODO: remove

	shaderParams->m_tex							= configs.texture->GetResource()->GetTextureRHI();
	shaderParams->m_texSampler					= TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp>::GetRHI();
	shaderParams->m_particlePosition			= rdgBuilder.CreateSRV(rdgRscsRef.particlePositionBuffer);
	shaderParams->m_particleLifespan			= rdgBuilder.CreateSRV(rdgRscsRef.particleLifespanBuffer);

	rdgBuilder.AddPass(RDG_EVENT_NAME("simpPtcRenderParticlePass"), shaderParams, ERDGPassFlags::Raster,
		[vs, ps, shaderParams, passParams, this, &configs]
		(FRHICommandList& rhiCmdList)
		{
			auto& sceneView		= *passParams->sceneView;

			float depthMaxDefault = 1.0;

			const FIntRect viewRect = ursRenderUtil::getRawViewRect_Unsafe(sceneView);
			rhiCmdList.SetViewport(viewRect.Min.X, viewRect.Min.Y, 0.0f, viewRect.Max.X, viewRect.Max.Y, depthMaxDefault);

			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			rhiCmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.bDepthBounds							= true;
			GraphicsPSOInit.DepthStencilAccess						= FExclusiveDepthStencil::DepthRead;
			GraphicsPSOInit.DepthStencilState						= TStaticDepthStencilState<false, CF_DepthNearOrEqual>::GetRHI();
			GraphicsPSOInit.BlendState								= TStaticBlendState<CW_RGBA, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha>::GetRHI();
			GraphicsPSOInit.RasterizerState							= TStaticRasterizerState<FM_Solid, CM_CCW>::GetRHI();
			GraphicsPSOInit.PrimitiveType							= PT_TriangleList;		// PT_TriangleStrip if 4 vtx
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= GMediaVertexDeclaration.VertexDeclarationRHI; // GMediaVertexDeclaration.VertexDeclarationRHI; //GetVertexDeclarationFVector4();		// TODO: need modify
			//GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= mesh->GetRenderData()->LODVertexFactories[0].VertexFactory.GetDeclaration();

			GraphicsPSOInit.BoundShaderState.VertexShaderRHI		= vs.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI			= ps.GetPixelShader();
			SetGraphicsPipelineState(rhiCmdList, GraphicsPSOInit, 0);
			
			SetShaderParameters(rhiCmdList, vs, vs.GetVertexShader(),	*shaderParams);
			SetShaderParameters(rhiCmdList, ps, ps.GetPixelShader(),	*shaderParams);

			#if 0
			auto* rdData = mesh->GetRenderData();
			auto& idxBuf = rdData->LODResources[0].IndexBuffer;

			FMeshDrawCommand cmd;
			mesh->GetRenderData()->LODVertexFactories[0].VertexFactory.GetStreams(GMaxRHIFeatureLevel, EVertexInputStreamType::Default, cmd.VertexStreams);
			cmd.IndexBuffer = idxBuf.IndexBufferRHI;

			//const int8 PrimitiveIdStreamIndex = (IsUniformBufferStaticSlotValid(SceneArgs.BatchedPrimitiveSlot) ? -1 : MeshDrawCommand.PrimitiveIdStreamIndex);
			for (int32 VertexBindingIndex = 0; VertexBindingIndex < cmd.VertexStreams.Num(); VertexBindingIndex++)
			{
				const FVertexInputStream& Stream = cmd.VertexStreams[VertexBindingIndex];
				rhiCmdList.SetStreamSource(Stream.StreamIndex, Stream.VertexBuffer, Stream.Offset);
				//StateCache.VertexStreams[Stream.StreamIndex] = Stream;
			}
			//MeshDrawCommand.ShaderBindings.SetOnCommandList(RHICmdList, MeshPipelineState.BoundShaderState.AsBoundShaderState(), StateCache.ShaderBindings);

			auto vtxCount = mesh->GetRenderData()->LODResources[0].GetNumVertices();
			auto primitiveCount = vtxCount / 3;
			auto instCount = configs.m_activeParticleCount;
			//rhiCmdList.DrawIndexedPrimitive(cmd.IndexBuffer, 0, 0, vtxCount, 0, primitiveCount, instCount);
			rhiCmdList.DrawIndexedPrimitive(cmd.IndexBuffer, 0, 0, vtxCount, 0, primitiveCount, 1);

			#else

			FBufferRHIRef VertexBuffer = ::createQuadVertexBuffer(rhiCmdList);
			rhiCmdList.SetStreamSource(0, VertexBuffer, 0);
			//rhiCmdList.DrawIndexedPrimitive(IndexBufferRHI, 0, 0, 4, 0, 2, configs.activeParticleCount);
			rhiCmdList.DrawPrimitive(0, 2, configs.activeParticleCount);

			#endif // 1
		}
	);
	#endif // 1
}

#endif