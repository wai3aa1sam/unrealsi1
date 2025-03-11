#include "ursDualKawaseBlur_Shaders.h"
#include "ursDualKawaseBlur.h"

//IMPLEMENT_GLOBAL_SHADER(FursDualKawaseBlur_CS,				"/urs_render/feature/post_processing/dual_kawase_blur/ursDualKawaseBlur_CS.usf",				"CS_main", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FursDualKawaseBlur_DownSampling_CS,	"/urs_render/feature/post_processing/dual_kawase_blur/ursDualKawaseBlur_CS.usf", "CS_downSampling", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FursDualKawaseBlur_UpSampling_CS,	"/urs_render/feature/post_processing/dual_kawase_blur/ursDualKawaseBlur_CS.usf", "CS_upSampling",	SF_Compute);

//IMPLEMENT_GLOBAL_SHADER(FursDualKawaseBlur_VS, "/urs_render/feature/post_processing/dual_kawase_blur/ursDualKawaseBlur_GraphicsShader.usf",	"VS_main", SF_Vertex);
//IMPLEMENT_GLOBAL_SHADER(FursDualKawaseBlur_PS, "/urs_render/feature/post_processing/dual_kawase_blur/ursDualKawaseBlur_GraphicsShader.usf",	"PS_main", SF_Pixel);

template<class TTo, class TFrom>
UE::Math::TIntPoint<TTo>
toIntPoint(const UE::Math::TVector2<TFrom>& v)
{
	return { static_cast<TTo>(v.X), static_cast<TTo>(v.Y) };
}

#if 0
#pragma mark --- FursDualKawaseBlur_CS-Impl ---
#endif // 0
#if 1

void
FursDualKawaseBlur_CS::createShaderParams(FParameters* outParams, FRDGBuilder& rdgBuilder, FursDualKawaseBlurParams_SamplingPass& passParams)
{
	const auto oneIntPoint = FIntPoint{ 1, 1 };
	//auto dstTexName = passParams.getDstTextureName();
	auto& srcTexDesc = passParams.srcTex->Desc;

	outParams->m_offsetFactor = passParams.offsetFactor;
	outParams->m_srcTexelSize = FVector2f::One() / FVector2f{passParams.srcTex->Desc.Extent};
	outParams->m_dstTexelSize = FVector2f::One() / FVector2f{passParams.dstTexExtent};
	outParams->m_dstTexExtent = passParams.dstTexExtent;

	outParams->m_srcTexSampler	= TStaticSamplerState<SF_Bilinear, AM_Clamp, AM_Clamp>::GetRHI();
	outParams->m_srcTex			= rdgBuilder.CreateSRV(passParams.srcTex);
	outParams->m_dstTex			= ursRdgUtil::createUavWithTexture2D(passParams.dstTex, rdgBuilder
		, passParams.isDownSampling ? TEXT("ursDKBlur_DownSamplingTex") : TEXT("ursDKBlur_UpSamplingTex")
		, passParams.dstTexExtent, srcTexDesc.Format, FClearValueBinding::Black, TexCreate_UAV | TexCreate_ShaderResource);
}

#endif

