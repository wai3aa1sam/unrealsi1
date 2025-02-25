#pragma once

#include "urs_core/common/urs_core_common.h"
#include "SceneViewExtension.h"

#if 0
#pragma mark --- FursSceneViewExtensionBase-Decl ---
#endif // 0
#if 1

class URS_CORE_API FursSceneViewExtensionBase : public FSceneViewExtensionBase
{
public:
	using Super = FSceneViewExtensionBase;

public:
	FursSceneViewExtensionBase(const FAutoRegister& autoReg);
	virtual ~FursSceneViewExtensionBase();

public:
	virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) = 0;
	virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) = 0;
	virtual void SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InViewInfo) override;
	virtual void SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData) override;

	virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) = 0;
	virtual void PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily) override;
	virtual void PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView) override;
	virtual void PreInitViews_RenderThread(FRDGBuilder& GraphBuilder) override;

	#if URS_ENGINE_VERSION_5_4_OR_HIGHER
	virtual void PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated) override;
	#endif
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

protected:
	void _SetupViewFamily(FSceneViewFamily& InViewFamily);
	void _SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView);
	void _BeginRenderViewFamily(FSceneViewFamily& InViewFamily);


private:

};

#endif