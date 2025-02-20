#include "ursSceneViewExtensionBase.h"

#if 0
#pragma mark --- FursSceneViewExtensionBase-Impl ---
#endif // 0
#if 1

FursSceneViewExtensionBase::FursSceneViewExtensionBase(const FAutoRegister& autoReg)
	: Super(autoReg)
{

}

FursSceneViewExtensionBase::~FursSceneViewExtensionBase()
{
}

void 
FursSceneViewExtensionBase::_SetupViewFamily(FSceneViewFamily& InViewFamily)
{
	//Super::SetupViewFamily(InViewFamily);

}

void 
FursSceneViewExtensionBase::_SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView)
{
	//Super::SetupView(InViewFamily, InView);

}

void
FursSceneViewExtensionBase::SetupViewPoint(APlayerController* Player, FMinimalViewInfo& InViewInfo)
{
	Super::SetupViewPoint(Player, InViewInfo);

}

void
FursSceneViewExtensionBase::SetupViewProjectionMatrix(FSceneViewProjectionData& InOutProjectionData)
{
	Super::SetupViewProjectionMatrix(InOutProjectionData);

}

void
FursSceneViewExtensionBase::_BeginRenderViewFamily(FSceneViewFamily& InViewFamily)
{
	//Super::BeginRenderViewFamily(InViewFamily);

}

void
FursSceneViewExtensionBase::PreRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	Super::PreRenderViewFamily_RenderThread(GraphBuilder, InViewFamily);

}

void 
FursSceneViewExtensionBase::PreRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	Super::PreRenderView_RenderThread(GraphBuilder, InView);

}

void
FursSceneViewExtensionBase::PreInitViews_RenderThread(FRDGBuilder& GraphBuilder)
{
	Super::PreInitViews_RenderThread(GraphBuilder);

}

void 
FursSceneViewExtensionBase::PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated)
{
	Super::PreRenderBasePass_RenderThread(GraphBuilder, bDepthBufferIsPopulated);

}

void
FursSceneViewExtensionBase::PostRenderBasePassDeferred_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView, const FRenderTargetBindingSlots& RenderTargets, TRDGUniformBufferRef<FSceneTextureUniformParameters> SceneTextures)
{
	Super::PostRenderBasePassDeferred_RenderThread(GraphBuilder, InView, RenderTargets, SceneTextures);

}

void 
FursSceneViewExtensionBase::PostRenderBasePassMobile_RenderThread(FRHICommandList& RHICmdList, FSceneView& InView)
{
	Super::PostRenderBasePassMobile_RenderThread(RHICmdList, InView);

}

void
FursSceneViewExtensionBase::PrePostProcessPass_RenderThread(FRDGBuilder& GraphBuilder, const FSceneView& View, const FPostProcessingInputs& Inputs)
{
	Super::PrePostProcessPass_RenderThread(GraphBuilder, View, Inputs);

}

void
FursSceneViewExtensionBase::SubscribeToPostProcessingPass(EPostProcessingPass Pass, FAfterPassCallbackDelegateArray& InOutPassCallbacks, bool bIsPassEnabled)
{
	Super::SubscribeToPostProcessingPass(Pass, InOutPassCallbacks, bIsPassEnabled);

}

void
FursSceneViewExtensionBase::PostRenderViewFamily_RenderThread(FRDGBuilder& GraphBuilder, FSceneViewFamily& InViewFamily)
{
	Super::PostRenderViewFamily_RenderThread(GraphBuilder, InViewFamily);

}

void 
FursSceneViewExtensionBase::PostRenderView_RenderThread(FRDGBuilder& GraphBuilder, FSceneView& InView)
{
	Super::PostRenderView_RenderThread(GraphBuilder, InView);

}

#endif