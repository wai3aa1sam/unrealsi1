#include "ursDualKawaseBlurSceneViewExt.h"

#include "ursDualKawaseBlur.h"
#include "ursDualKawaseBlur_Shaders.h"

DECLARE_GPU_STAT(ursDkBlur_Blur);
DECLARE_GPU_STAT(ursDkBlur_RenderScreen);
DECLARE_GPU_STAT(ursDkBlur_CopyToScreen);

#if 0
#pragma mark --- FursDualKawaseBlurSceneViewExt-Impl ---
#endif // 0
#if 1

FursDualKawaseBlurSceneViewExt::FursDualKawaseBlurSceneViewExt(const FAutoRegister& autoReg, AursDualKawaseBlur* simpleParticle)
	: Super(autoReg)
{
	_simpleParticle = simpleParticle;
}

FursDualKawaseBlurSceneViewExt::~FursDualKawaseBlurSceneViewExt()
{
}

void 
FursDualKawaseBlurSceneViewExt::requestExecute(const FursDualKawaseBlurConfigs& configs)
{
	_pipelineParams.configs = configs;
}

void 
FursDualKawaseBlurSceneViewExt::SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	Super::_SetupViewFamily(InViewFamily);

}

void 
FursDualKawaseBlurSceneViewExt::SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	Super::_SetupView(InViewFamily, InView);

}

void
FursDualKawaseBlurSceneViewExt::SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InViewInfo)
{
	Super::SetupViewPoint(Player, InViewInfo);

}

void
FursDualKawaseBlurSceneViewExt::SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData)
{
	Super::SetupViewProjectionMatrix(InOutProjectionData);

}

void
FursDualKawaseBlurSceneViewExt::BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	Super::_BeginRenderViewFamily(InViewFamily);

}

void
FursDualKawaseBlurSceneViewExt::PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	Super::PreRenderViewFamily_RenderThread(GraphBuilder, InViewFamily);

}

void 
FursDualKawaseBlurSceneViewExt::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	Super::PreRenderView_RenderThread(GraphBuilder, InView);

}

void
FursDualKawaseBlurSceneViewExt::PreInitViews_RenderThread(FRDGBuilder& GraphBuilder)
{
	Super::PreInitViews_RenderThread(GraphBuilder);

}

#if URS_ENGINE_VERSION_5_4_OR_HIGHER
void 
FursDualKawaseBlurSceneViewExt::PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated)
{
	Super::PreRenderBasePass_RenderThread(GraphBuilder, bDepthBufferIsPopulated);

}
#endif

void
FursDualKawaseBlurSceneViewExt::PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures)
{
	Super::PostRenderBasePassDeferred_RenderThread(GraphBuilder, InView, RenderTargets, SceneTextures);

}

void 
FursDualKawaseBlurSceneViewExt::PostRenderBasePassMobile_RenderThread(FRHICommandList& RHICmdList, FSceneView& InView)
{
	Super::PostRenderBasePassMobile_RenderThread(RHICmdList, InView);

}

void
FursDualKawaseBlurSceneViewExt::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	Super::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

	execute(GraphBuilder, View);
}

void
FursDualKawaseBlurSceneViewExt::SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
{
	Super::SubscribeToPostProcessingPass(Pass, InOutPassCallbacks, bIsPassEnabled);

}

void
FursDualKawaseBlurSceneViewExt::PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	Super::PostRenderViewFamily_RenderThread(GraphBuilder, InViewFamily);

}

void 
FursDualKawaseBlurSceneViewExt::PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	Super::PostRenderView_RenderThread(GraphBuilder, InView);

}

void 
FursDualKawaseBlurSceneViewExt::execute(FRDGBuilder& GraphBuilder, const FSceneView& View)
{
	auto& pipelineParams	= _pipelineParams;
	auto& configs			= pipelineParams.configs;
	if (!configs.isExecuteBlur)
		return;

	const auto&				viewInfo = ursSceneViewUtil::getViewInfo_Unsafe(View);
	const FRDGTextureRef&	inputTex = viewInfo.GetSceneTextures().Color.Target;

	pipelineParams.sceneView = &View;
	pipelineParams.inputTex = inputTex;

	auto& rdgBuilder = GraphBuilder;
	auto* passBlur = addBlurPass(rdgBuilder, pipelineParams);

	if (passBlur && configs.isCopyToScreen)
	{
		RDG_GPU_STAT_SCOPE(rdgBuilder, ursDkBlur_CopyToScreen);

		FRHICopyTextureInfo copyInfo = {};
		copyInfo.Size = FIntVector {inputTex->Desc.Extent.X, inputTex->Desc.Extent.Y, 1 };
		AddCopyTexturePass(rdgBuilder, pipelineParams.blurredTex, inputTex, copyInfo);
	}
}

FRDGPassRef
FursDualKawaseBlurSceneViewExt::addBlurPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams)
{
	RDG_GPU_STAT_SCOPE(rdgBuilder, ursDkBlur_Blur);

	auto& configs			= pipelineParams.configs;
	/*if (!configs.isValid())
	return;*/

	auto& inputTex = pipelineParams.inputTex;
	auto inputTexSize = inputTex->Desc.Extent;

	FRDGPassRef		lastPass	= nullptr;
	FRDGTextureRef	lastTex		= inputTex;

	static constexpr uint32 s_maxSamplingIterCount = 8;

	uint32 samplingIterCount = FMath::Log2(configs.blurRadius);		// instead of fixed n iter, determined by the radius
	samplingIterCount = FMath::Min(samplingIterCount, s_maxSamplingIterCount);

	uint32 totalSamplingIterCount = samplingIterCount * 2;
	for (uint32 i = 0; i < totalSamplingIterCount; i++)
	{
		bool isDownSampling = i < samplingIterCount;
		uint32 samplingIterIdx = isDownSampling ? i : i - samplingIterCount;

		FursDualKawaseBlurParams_SamplingPass& samplingPassParams = pipelineParams.samplingPassParams;
		samplingPassParams.create(lastPass, samplingIterIdx, configs.sampleOffset, lastTex, isDownSampling);

		FRDGPassRef pass = _addBlurSamplingPass(rdgBuilder, pipelineParams);
		lastTex		= samplingPassParams.dstTex;
		lastPass	= pass;
	}

	pipelineParams.blurredTex = lastTex;

	return lastPass;
}

FRDGPassRef 
FursDualKawaseBlurSceneViewExt::_addBlurSamplingPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams)
{

	//DECLARE_GPU_STAT(ursSimpleParticle_RenderParticle);
	//RDG_GPU_STAT_SCOPE(rdgBuilder, ursSimpleParticle_RenderParticle);

	// TODO: a scoped stat
	//RDG_CSV_STAT_EXCLUSIVE_SCOPE(GraphBuilder, RenderBasePass);
	//SCOPED_NAMED_EVENT(FDeferredShadingSceneRenderer_RenderBasePass, FColor::Emerald);

	const auto& configs = pipelineParams.configs;
	auto& samplingPassParams = pipelineParams.samplingPassParams;

	TShaderMapRef<FursDualKawaseBlur_DownSampling_CS>	cs(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	auto* params = rdgBuilder.AllocParameters<FursDualKawaseBlur_CS::FParameters>();	// 
	cs->createShaderParams(params, rdgBuilder, samplingPassParams);
	
	auto iterIdx = samplingPassParams.iterIndex;
	auto srcTexExtent = samplingPassParams.srcTex->Desc.Extent;
	auto dstTexExtent = samplingPassParams.dstTex->Desc.Extent;

	FRDGPassRef pass = nullptr;
	//auto& cs = samplingPassParams.isDownSampling ? csDown : csUp;
	if (samplingPassParams.isDownSampling)
	{
		pass = FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("ursDKBlur_DownSamplingPass_%d [%d, %d] -> [%d, %d]", iterIdx, srcTexExtent.X, srcTexExtent.Y, dstTexExtent.X, dstTexExtent.Y)
			, cs, params, FComputeShaderUtils::GetGroupCount(dstTexExtent, configs.numThreads));
	}
	else
	{
		TShaderMapRef<FursDualKawaseBlur_UpSampling_CS>		csUp(GetGlobalShaderMap(GMaxRHIFeatureLevel));
		pass = FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("ursDKBlur_UpSamplingPass_%d [%d, %d] -> [%d, %d]", iterIdx, srcTexExtent.X, srcTexExtent.Y, dstTexExtent.X, dstTexExtent.Y)
			, csUp, params, FComputeShaderUtils::GetGroupCount(dstTexExtent, configs.numThreads));
	}

	#if 0
	if (samplingPassParams.lastPass)
	{
		rdgBuilder.AddPassDependency(samplingPassParams.lastPass, pass);
	}
	#endif // 0

	return pass;
}

FRDGPassRef
FursDualKawaseBlurSceneViewExt::addRenderScreenPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams)
{
	RDG_GPU_STAT_SCOPE(rdgBuilder, ursDkBlur_RenderScreen);

	// TODO: a scoped stat
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_BasePass));
	//RenderBasePassInternal(GraphBuilder, InViews, SceneTextures, BasePassRenderTargets, BasePassDepthStencilAccess, ForwardBasePassTextures, DBufferTextures, bDoParallelBasePass, bRenderLightmapDensity, InstanceCullingManager, bNaniteEnabled, NaniteBasePassShadingCommands, NaniteRasterResults);
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_AfterBasePass));

	// AddDrawScreenPass

	return nullptr;
}

#endif