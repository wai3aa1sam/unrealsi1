#pragma once

#include "ursDualKawaseBlur_Common.h"

class AursDualKawaseBlur;

#if 0
#pragma mark --- FursDualKawaseBlurSceneViewExt-Decl ---
#endif // 0
#if 1

class URS_RENDER_API FursDualKawaseBlurSceneViewExt : public FursSceneViewExtensionBase
{
public:
	using Super				= FursSceneViewExtensionBase;
	using PipelineParams	= FursDualKawaseBlurParams_Pipeline;

public:
	FursDualKawaseBlurSceneViewExt(const FAutoRegister& autoReg, AursDualKawaseBlur* simpleParticle);
	virtual ~FursDualKawaseBlurSceneViewExt();

public:
	void requestExecute(const FursDualKawaseBlurConfigs& configs);

public:
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;
	virtual void SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InViewInfo) override;
	virtual void SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData) override;

	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;
	virtual void PreInitViews_RenderThread(FRDGBuilder& GraphBuilder) override;

	#if URS_ENGINE_VERSION_5_4_OR_HIGHER
	virtual void PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated) override;
	#endif // URS_ENGINE_VERSION_5_4_OR_HIGHER

	virtual void PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures) override;
	virtual void PostRenderBasePassMobile_RenderThread(FRHICommandList& RHICmdList, FSceneView& InView) override;

	virtual void PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs) override;
	virtual void SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled) override;

	virtual void PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;
	virtual void PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;

public:
	virtual int32 GetPriority() const override { return 0; }

protected:
	virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override { return true; }

private:
	void execute(FRDGBuilder& GraphBuilder, const FSceneView& View);

	void profileCompareToUnreal(FRDGBuilder& GraphBuilder, const FSceneView& View);
	void profileUnrealBloomBlur(FRDGBuilder& GraphBuilder, const FSceneView& View);

private:
	FRDGPassRef addBlurPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams);
	FRDGPassRef _addBlurSamplingPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams);
	FRDGPassRef addRenderToScreenPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams);
	FRDGPassRef addCopyToScreenPass(FRDGBuilder& rdgBuilder, PipelineParams& pipelineParams);

private:
	TWeakObjectPtr<AursDualKawaseBlur> _simpleParticle = nullptr;
	PipelineParams _pipelineParams;
};

#endif