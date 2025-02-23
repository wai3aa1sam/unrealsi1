#include "ursSimpleParticleSceneViewExt.h"

#include "ursSimpleParticle.h"

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

void 
FursSimpleParticleSceneViewExt::PreRenderBasePass_RenderThread(FRDGBuilder& GraphBuilder, bool bDepthBufferIsPopulated)
{
	Super::PreRenderBasePass_RenderThread(GraphBuilder, bDepthBufferIsPopulated);

}

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
	
	auto* simpleParticle = _simpleParticle.Get();
	if (simpleParticle)
	{
		simpleParticle->RenderThread_render(GraphBuilder, View);
	}
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

#endif