#include "ursDualKawaseBlur_Common.h"

#include "urs_render/feature/particle_system/simple_particle/ursSimpleParticle.h"
#include "ursDualKawaseBlurSceneViewExt.h"

void 
FursDualKawaseBlurConfigs::tick(float dt, FursDualKawaseBlurSceneViewExt& dkBlurSVExt)
{
	if (isShowDemo && demoActor)
	{
		#if 0
		if (_demoCurve)
		{
			//float demoCurveMinTime, demoCurveMaxTime;
			//_demoCurve->GetTimeRange(demoCurveMinTime, demoCurveMaxTime);
			//float demoCurveLength = demoCurveMaxTime - demoCurveMinTime;

			////float TimeNormalized = FMath::Clamp(_demoCurveTimer / demoCurveLength, 0.0f, 1.0f);
			//float demoCurveTime = demoCurveMinTime + FMath::Fmod(_demoCurveTimer, demoCurveLength);
			//_demoValue = _demoCurve->GetFloatValue(demoCurveTime);
		}
		#endif // 0
		if (demoBlurSpeed > 0.0)
		{
			blurRadius = FMath::Clamp(maxBlurRadius * ((FMath::Sin(demoBlurTimer * demoBlurSpeed) + 1.0f) * 0.5f), 1, maxBlurRadius);
		}

		demoBlurTimer += dt * demoTimeScale;
		demoActor->Tick(dt);
	}

	if (isExecuteBlur)
	{
		dkBlurSVExt.requestExecute(*this);
	}
}

void 
FursDualKawaseBlurParams_SamplingPass::create(FRDGPassRef lastPass_, uint32 iterIndex_, float offsetFactor_, FRDGTextureRef srcTex_, bool isDownSampling_)
{
	URS_ASSERT(srcTex_->Desc.IsTexture2D());

	lastPass		= lastPass_;
	iterIndex		= iterIndex_;
	offsetFactor	= offsetFactor_;
	isDownSampling	= isDownSampling_;
	srcTex			= srcTex_;

	auto srcTexExtent = srcTex_->Desc.Extent;
	//dstTexExtent.X	= isDownSampling ? FMath::Max(static_cast<float>(FMath::DivideAndRoundUp(srcTexExtent.X, 2)), 1.0) : FMath::Max(srcTexExtent.X * 2.0, 1.0);
	//dstTexExtent.Y	= isDownSampling ? FMath::Max(static_cast<float>(FMath::DivideAndRoundUp(srcTexExtent.Y, 2)), 1.0) : FMath::Max(srcTexExtent.Y * 2.0, 1.0);
	dstTexExtent.X	= isDownSampling ? FMath::Max(FMath::DivideAndRoundUp(srcTexExtent.X, 2), 1.0) : FMath::Max(srcTexExtent.X * 2.0, 1.0);
	dstTexExtent.Y	= isDownSampling ? FMath::Max(FMath::DivideAndRoundUp(srcTexExtent.Y, 2), 1.0) : FMath::Max(srcTexExtent.Y * 2.0, 1.0);
}

void 
FursDualKawaseBlurParams_SamplingPass::getPassNameTo(FString& out) const
{
	URS_ASSERT(false, "do not use, all rdg name is ptr only, wont alloc");
	auto srcTexExtent = srcTex->Desc.Extent;
	out = isDownSampling ? 
			ursFormat("ursDKBlur_DownSamplingPass_{} {} -> {}", iterIndex, srcTexExtent, dstTexExtent)
			: ursFormat("ursDKBlur_UpSamplingPass_{} {} -> {}", iterIndex, srcTexExtent, dstTexExtent)
	;
}

FRDGEventName 
FursDualKawaseBlurParams_SamplingPass::getRdgEventName() const
{
	URS_ASSERT(false, "do not use, all rdg name is ptr only, wont alloc");
	FString passName;
	getPassNameTo(passName);
	return FRDGEventName{*passName};
}

void 
FursDualKawaseBlurParams_SamplingPass::getDstTextureNameTo(FString& out) const
{
	URS_ASSERT(false, "do not use, all rdg name is ptr only, wont alloc");
	out = isDownSampling ?
		ursFormat("ursDKBlur_DownSampling_Texture_{}", iterIndex)
		: ursFormat("ursDKBlur_UpSampling_Texture_{}", iterIndex)
	;
}

