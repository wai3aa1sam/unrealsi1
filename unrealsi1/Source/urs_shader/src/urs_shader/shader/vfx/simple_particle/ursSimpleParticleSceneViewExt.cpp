#include "ursSimpleParticleSceneViewExt.h"

#include "ursSimpleParticle.h"
#include "ursSimpleParticle_Shaders.h"

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

#if URS_ENGINE_VERSION_5_4_OR_HIGHER
void 
FursSimpleParticleSceneViewExt::PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated)
{
	Super::PreRenderBasePass_RenderThread(GraphBuilder, bDepthBufferIsPopulated);

}
#endif

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
	// TODO: a scoped stat
	//RDG_CSV_STAT_EXCLUSIVE_SCOPE(GraphBuilder, RenderBasePass);
	//SCOPED_NAMED_EVENT(FDeferredShadingSceneRenderer_RenderBasePass, FColor::Emerald);

	const auto& configs = passParams->configs;

	if (!configs.isValid())
		return;

	TShaderMapRef<FursSimpleParticle_CS> cs(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	auto* params = rdgBuilder.AllocParameters<FursSimpleParticle_CS::FParameters>();	// 
	cs->setupShaderParams(params, rdgBuilder, _passParams);
	FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("ursSimulateParticlePass"), cs, params, FIntVector(configs.getThreadGroup(), 1, 1));
}

void 
FursSimpleParticleSceneViewExt::addRenderParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams)
{
	// TODO: a scoped stat
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_BasePass));
	//RenderBasePassInternal(GraphBuilder, InViews, SceneTextures, BasePassRenderTargets, BasePassDepthStencilAccess, ForwardBasePassTextures, DBufferTextures, bDoParallelBasePass, bRenderLightmapDensity, InstanceCullingManager, bNaniteEnabled, NaniteBasePassShadingCommands, NaniteRasterResults);
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_AfterBasePass));

	// if (SubmitDrawBegin(MeshDrawCommand, GraphicsMinimalPipelineStateSet, SceneArgs, InstanceFactor, RHICmdList, StateCache, bAllowSkipDrawCommand))
	// AddSimpleMeshPass(

	auto& rhiCmdList	= rdgBuilder.RHICmdList;
	auto& sceneView		= *passParams->sceneView;
	auto& rdgRscsRef	= passParams->rdgRscsRef;
	const auto& configs	= passParams->configs;

	if (!rdgRscsRef.particlePositionBuffer)
		return;

	#if 1
	FGlobalShaderMap* shaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FursSimpleParticle_VS> vs{shaderMap};
	TShaderMapRef<FursSimpleParticle_PS> ps{shaderMap};

	auto* shaderParams = rdgBuilder.AllocParameters<FursSimpleParticle_PS::FParameters>();

	auto& viewInfo = ursSceneViewUtil::getViewInfo_Unsafe(sceneView);

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

	rdgBuilder.AddPass(RDG_EVENT_NAME("ursRenderParticlePass"), shaderParams, ERDGPassFlags::Raster,
		[vs, ps, shaderParams, passParams, this, &configs]
		(FRHICommandList& rhiCmdList)
		{
			auto& sceneView		= *passParams->sceneView;

			float depthMaxDefault = 1.0;

			const FIntRect viewRect = ursSceneViewUtil::getRawViewRect_Unsafe(sceneView);
			rhiCmdList.SetViewport(viewRect.Min.X, viewRect.Min.Y, 0.0f, viewRect.Max.X, viewRect.Max.Y, depthMaxDefault);

			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			rhiCmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.bDepthBounds							= true;
			GraphicsPSOInit.DepthStencilAccess						= FExclusiveDepthStencil::DepthRead;
			GraphicsPSOInit.DepthStencilState						= TStaticDepthStencilState<false, CF_DepthNearOrEqual>::GetRHI();
			GraphicsPSOInit.BlendState								= TStaticBlendState<CW_RGBA, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add, BF_SourceAlpha, BF_InverseDestAlpha>::GetRHI();
			//GraphicsPSOInit.BlendState								= ursRenderUtil::getBlendStateRhi(EBlendMode::BLEND_Translucent);
			GraphicsPSOInit.RasterizerState							= TStaticRasterizerState<FM_Solid, CM_CCW>::GetRHI();
			GraphicsPSOInit.PrimitiveType							= PT_TriangleStrip;		// PT_TriangleStrip if 4 vtx, PT_TriangleList if with vtxBuf
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= urs_g_vertexDecl_PosColor.vertexDeclRHI;

			GraphicsPSOInit.BoundShaderState.VertexShaderRHI		= vs.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI			= ps.GetPixelShader();
			SetGraphicsPipelineState(rhiCmdList, GraphicsPSOInit, 0);
			
			SetShaderParameters(rhiCmdList, vs, vs.GetVertexShader(),	*shaderParams);
			SetShaderParameters(rhiCmdList, ps, ps.GetPixelShader(),	*shaderParams);

			static FBufferRHIRef vtxBuf = ursMeshAssetUtil::createQuadVertexBuffer(rhiCmdList, false);		// TODO: place as a global asset
			static FBufferRHIRef idxBuf = ursMeshAssetUtil::createQuadIndexBuffer(rhiCmdList);				// TODO: place as a global asset

			rhiCmdList.SetStreamSource(0, vtxBuf, 0);
			//rhiCmdList.DrawIndexedPrimitive(IndexBufferRHI, 0, 0, 4, 0, 2, configs.activeParticleCount);
			rhiCmdList.DrawPrimitive(0, 2, configs.activeParticleCount);
		}
	);
	#endif // 1
}

#endif