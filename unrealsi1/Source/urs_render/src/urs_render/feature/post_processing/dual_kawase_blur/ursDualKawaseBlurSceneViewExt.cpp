#include "ursDualKawaseBlurSceneViewExt.h"

#include "ursDualKawaseBlur.h"
#include "ursDualKawaseBlur_Shaders.h"

#include <Runtime/Renderer/Private/SceneTextureParameters.h>
#include <Runtime/Renderer/Private/PostProcess/PostProcessBloomSetup.h>
#include <Runtime/Renderer/Private/PostProcess/PostProcessDownsample.h>
#include <Runtime/Renderer/Private/PostProcess/PostProcessEyeAdaptation.h>
#include <Runtime/Renderer/Private/PostProcess/PostProcessHistogram.h>
#include <Runtime/Renderer/Private/PostProcess/PostProcessLocalExposure.h>

DECLARE_GPU_STAT(ursDkBlur);
DECLARE_GPU_STAT(ursDkBlur_Blur);
DECLARE_GPU_STAT(ursDkBlur_BlurSampling);
DECLARE_GPU_STAT(ursDkBlur_RenderToScreen);
DECLARE_GPU_STAT(ursDkBlur_CopyToScreen);

DECLARE_GPU_STAT(ursDkBlur_ProfileUnrealBloomBlur);

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

	//execute(GraphBuilder, View);
	profileCompareToUnreal(GraphBuilder, View);
	//profileUnrealBloomBlur(GraphBuilder, View);
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

	auto& rdgBuilder = GraphBuilder;
	URS_GPU_PROFILE_SCOPE(GraphBuilder, ursDkBlur);

	const auto&				viewInfo = ursSceneViewUtil::getViewInfo_Unsafe(View);
	const FRDGTextureRef&	inputTex = viewInfo.GetSceneTextures().Color.Target;

	pipelineParams.sceneView = &View;
	pipelineParams.inputTex = inputTex;

	auto* passBlur = addBlurPass(rdgBuilder, pipelineParams);
	if (passBlur && configs.isRenderToScreen)
	{
		addRenderToScreenPass(rdgBuilder, pipelineParams);
	}
}

FRDGPassRef
FursDualKawaseBlurSceneViewExt::addBlurPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams)
{
	URS_GPU_PROFILE_SCOPE(rdgBuilder, ursDkBlur_Blur);

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
	URS_GPU_PROFILE_SCOPE(rdgBuilder, ursDkBlur_BlurSampling);

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

	auto passFlags = ERDGPassFlags::Compute | ERDGPassFlags::NeverCull;
	FRDGPassRef pass = nullptr;
	//auto& cs = samplingPassParams.isDownSampling ? csDown : csUp;
	if (samplingPassParams.isDownSampling)
	{
		pass = FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("ursDKBlur_DownSamplingPass_%d [%d, %d] -> [%d, %d]", iterIdx, srcTexExtent.X, srcTexExtent.Y, dstTexExtent.X, dstTexExtent.Y)
			, passFlags, cs, params, FComputeShaderUtils::GetGroupCount(dstTexExtent, configs.numThreads));
	}
	else
	{
		TShaderMapRef<FursDualKawaseBlur_UpSampling_CS>		csUp(GetGlobalShaderMap(GMaxRHIFeatureLevel));
		pass = FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("ursDKBlur_UpSamplingPass_%d [%d, %d] -> [%d, %d]", iterIdx, srcTexExtent.X, srcTexExtent.Y, dstTexExtent.X, dstTexExtent.Y)
			, passFlags, csUp, params, FComputeShaderUtils::GetGroupCount(dstTexExtent, configs.numThreads));
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
FursDualKawaseBlurSceneViewExt::addCopyToScreenPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams)
{
	URS_GPU_PROFILE_SCOPE(rdgBuilder, ursDkBlur_CopyToScreen);

	auto& inputTex = pipelineParams.inputTex;

	FRHICopyTextureInfo copyInfo = {};
	copyInfo.Size = FIntVector {inputTex->Desc.Extent.X, inputTex->Desc.Extent.Y, 1 };
	AddCopyTexturePass(rdgBuilder, pipelineParams.blurredTex, inputTex, copyInfo);

	return nullptr;
}

FRDGPassRef
FursDualKawaseBlurSceneViewExt::addRenderToScreenPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams)
{
	URS_GPU_PROFILE_SCOPE(rdgBuilder, ursDkBlur_RenderToScreen);

	const auto&	viewInfo = ursSceneViewUtil::getViewInfo_Unsafe(*pipelineParams.sceneView);

	auto& inputTex	= pipelineParams.blurredTex;
	auto& outputTex = pipelineParams.inputTex;

	const FScreenPassTextureViewport inputViewport(inputTex);
	const FScreenPassTextureViewport outputViewport(outputTex);

	auto srcTexExtent = inputTex->Desc.Extent;
	auto dstTexExtent = outputTex->Desc.Extent;

	TShaderMapRef<FScreenPassVS>			vs(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	TShaderMapRef<FursDualKawaseBlur_PS>	ps(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	auto* shaderParams = rdgBuilder.AllocParameters<FursDualKawaseBlur_PS::FParameters>();
	shaderParams->RenderTargets[0]	= FRenderTargetBinding(outputTex, ERenderTargetLoadAction::ELoad);
	shaderParams->m_srcTex			= rdgBuilder.CreateSRV(inputTex);
	shaderParams->m_srcTexSampler	= TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp>::GetRHI();

	AddDrawScreenPass(rdgBuilder
		, RDG_EVENT_NAME("ursDKBlur_RenderToScreenPass [%d, %d] -> [%d, %d]", srcTexExtent.X, srcTexExtent.Y, dstTexExtent.X, dstTexExtent.Y)
		, viewInfo, outputViewport, inputViewport, vs, ps, shaderParams
	);

	return nullptr;
}

void 
FursDualKawaseBlurSceneViewExt::profileCompareToUnreal(FRDGBuilder& GraphBuilder, const FSceneView& View)
{
	auto& pipelineParams	= _pipelineParams;
	auto& configs			= pipelineParams.configs;
	if (!configs.isExecuteBlur)
		return;

	auto& rdgBuilder = GraphBuilder;
	URS_GPU_PROFILE_SCOPE(GraphBuilder, ursDkBlur);

	const auto&				viewInfo = ursSceneViewUtil::getViewInfo_Unsafe(View);
	const FRDGTextureRef&	inputTex = viewInfo.GetSceneTextures().Color.Target;

	pipelineParams.sceneView = &View;
	pipelineParams.inputTex = inputTex;

	FRDGTextureRef halfResTex = nullptr;
	{
		FursDualKawaseBlurParams_SamplingPass& samplingPassParams = pipelineParams.samplingPassParams;
		samplingPassParams.create(nullptr, 0, 1.0f, inputTex, true);
		_addBlurSamplingPass(rdgBuilder, pipelineParams);
		halfResTex = samplingPassParams.dstTex;
	}

	{
		pipelineParams.inputTex = halfResTex;
		auto* passBlur = addBlurPass(rdgBuilder, pipelineParams);
		if (passBlur && configs.isRenderToScreen)
		//if (configs.isRenderToScreen)
		{
			pipelineParams.inputTex = inputTex;
			addRenderToScreenPass(rdgBuilder, pipelineParams);
		}
	}
}

void 
FursDualKawaseBlurSceneViewExt::profileUnrealBloomBlur(FRDGBuilder& GraphBuilder, const FSceneView& View)
{
	#if 0
	URS_GPU_PROFILE_SCOPE(GraphBuilder, ursDkBlur_ProfileUnrealBloomBlur);

	const auto&	viewInfo = ursSceneViewUtil::getViewInfo_Unsafe(View);

	const FEngineShowFlags& EngineShowFlags = View.Family->EngineShowFlags;
	bool CVarBloomApplyLocalExposure = true;
	EDownsampleQuality CVarDownsampleChainQuality = EDownsampleQuality::High;		// TEXT(" 1: high quality (default)\n"),

	const FScreenPassTexture BlackDummy(GSystemTextures.GetBlackDummy(GraphBuilder));
	FRDGTextureRef LocalExposureBlurredLogLumTexture = BlackDummy.Texture;

	FRDGTextureRef LocalExposureTexture = nullptr;

	FScreenPassTexture			SceneColor(viewInfo.GetSceneTextures().Color.Target, viewInfo.ViewRect);
	FScreenPassTextureSlice		inputTex = FScreenPassTextureSlice::CreateFromScreenPassTexture(GraphBuilder, SceneColor);;

	FSceneDownsampleChain BloomDownsampleChain;

	FLocalExposureParameters LocalExposureParameters;
	const FEyeAdaptationParameters EyeAdaptationParameters = GetEyeAdaptationParameters(viewInfo);

	FScreenPassTexture Bloom;

	{
		//FScreenPassTextureSlice LocalExposureSceneColor = bProcessEighthResolution ? EighthResSceneColor : (bProcessQuarterResolution ? QuarterResSceneColor : HalfResSceneColor);
		FScreenPassTextureSlice LocalExposureSceneColor = inputTex;

		const bool bLocalExposureEnabled =
			EngineShowFlags.VisualizeLocalExposure ||
			!FMath::IsNearlyEqual(View.FinalPostProcessSettings.LocalExposureHighlightContrastScale, 1.0f) ||
			!FMath::IsNearlyEqual(View.FinalPostProcessSettings.LocalExposureShadowContrastScale, 1.0f) ||
			View.FinalPostProcessSettings.LocalExposureHighlightContrastCurve ||
			View.FinalPostProcessSettings.LocalExposureShadowContrastCurve ||
			!FMath::IsNearlyEqual(View.FinalPostProcessSettings.LocalExposureDetailStrength, 1.0f);

		if (bLocalExposureEnabled)
		{
			LocalExposureTexture = AddLocalExposurePass(
				GraphBuilder, viewInfo,
				EyeAdaptationParameters,
				LocalExposureSceneColor);
		}

		LocalExposureParameters = GetLocalExposureParameters(viewInfo, LocalExposureSceneColor.ViewRect.Size(), EyeAdaptationParameters);
	}

	{
		const bool bBloomSetupRequiredEnabled = View.FinalPostProcessSettings.BloomThreshold > -1.0f || LocalExposureTexture != nullptr;

		//FScreenPassTextureSlice DownsampleInput = bProcessEighthResolution ? EighthResSceneColor : (bProcessQuarterResolution ? QuarterResSceneColor : HalfResSceneColor);

		FRDGBufferRef LastEyeAdaptationBuffer = GetEyeAdaptationBuffer(GraphBuilder, viewInfo);
		FRDGBufferRef EyeAdaptationBuffer = LastEyeAdaptationBuffer;

		const FSceneDownsampleChain* LensFlareSceneDownsampleChain = nullptr;

		{
			//FScreenPassTextureSlice DownsampleInput = bProcessEighthResolution ? EighthResSceneColor : (bProcessQuarterResolution ? QuarterResSceneColor : HalfResSceneColor);
			FScreenPassTextureSlice DownsampleInput = inputTex;

			if (bBloomSetupRequiredEnabled)
			{
				const float BloomThreshold = View.FinalPostProcessSettings.BloomThreshold;

				FBloomSetupInputs SetupPassInputs;
				SetupPassInputs.SceneColor						= DownsampleInput;
				SetupPassInputs.EyeAdaptationBuffer				= EyeAdaptationBuffer;
				SetupPassInputs.EyeAdaptationParameters			= &EyeAdaptationParameters;
				SetupPassInputs.LocalExposureParameters			= &LocalExposureParameters;
				SetupPassInputs.LocalExposureTexture			= CVarBloomApplyLocalExposure ? LocalExposureTexture : nullptr;
				SetupPassInputs.BlurredLogLuminanceTexture		= LocalExposureBlurredLogLumTexture;
				SetupPassInputs.Threshold						= BloomThreshold;

				DownsampleInput = FScreenPassTextureSlice::CreateFromScreenPassTexture(GraphBuilder, AddBloomSetupPass(GraphBuilder, viewInfo, SetupPassInputs));
			}

			const bool bLogLumaInAlpha = false;
			BloomDownsampleChain.Init(GraphBuilder, viewInfo, EyeAdaptationParameters, DownsampleInput, CVarDownsampleChainQuality, bLogLumaInAlpha);

			LensFlareSceneDownsampleChain = &BloomDownsampleChain;
		}

		Bloom = AddGaussianBloomPasses(GraphBuilder, viewInfo, LensFlareSceneDownsampleChain);
	}

	#else
	URS_ASSERT(false, "cannot use non export fn");
	#endif // 0
}



#endif