#pragma once

#include "ursSimpleParticle_Common.h"

class AursSimpleParticle;


#if 0
#pragma mark --- FursSimpleParticleSceneViewExt-Decl ---
#endif // 0
#if 1

class URS_RENDER_API FursSimpleParticleSceneViewExt : public FursSceneViewExtensionBase
{
public:
	using Super			= FursSceneViewExtensionBase;
	using PassParams	= FursSimpleParticleParams_Pass;

public:
	FursSimpleParticleSceneViewExt(const FAutoRegister& autoReg, AursSimpleParticle* simpleParticle);
	virtual ~FursSimpleParticleSceneViewExt();

public:
	void requestExecute(const FursSimpleParticleConfigs& configs);

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
	void addSimulateParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams);
	void addRenderParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams);

private:
	TWeakObjectPtr<AursSimpleParticle> _simpleParticle = nullptr;
	FursSimpleParticleParams_Pass _passParams;
};

#endif