#pragma once

#include "urs_render/feature/urs_render_feature_common.h"

#include "ursDualKawaseBlur_Common.generated.h"

class AursSimpleParticle;
class FursDualKawaseBlurSceneViewExt;

USTRUCT()
struct URS_RENDER_API FursDualKawaseBlurConfigs
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) uint32	numThreads			= 8;
	UPROPERTY(EditAnywhere) uint8	isExecuteBlur		: 1;

	UPROPERTY(EditAnywhere, meta=(ClampMin = 1, ClampMax = 255)) float	maxBlurRadius	= 15.0;
	UPROPERTY(EditAnywhere, meta=(ClampMin = 1, ClampMax = 255)) float	blurRadius		= 15.0;
	UPROPERTY(EditAnywhere) float	sampleOffset	= 1.0;

	UPROPERTY(EditAnywhere) TObjectPtr<AursSimpleParticle>	demoActor = nullptr;
	UPROPERTY(EditAnywhere) float							demoTimeScale		= 1.0;
	UPROPERTY(EditAnywhere)	float							demoBlurTimer		= 0.0;
	UPROPERTY(EditAnywhere)	float							demoBlurSpeed		= 1.0;
	UPROPERTY(EditAnywhere)	uint8							isShowDemo			: 1;
	UPROPERTY(EditAnywhere)	uint8							isProfile			: 1;
	UPROPERTY(EditAnywhere) uint8							isRenderToScreen	: 1;

public:
	FursDualKawaseBlurConfigs() : isExecuteBlur(false) {}

public:
	void tick(float dt, FursDualKawaseBlurSceneViewExt& dkBlurSVExt);
};

struct FursDualKawaseBlurParams_SamplingPass
{
	uint32	numThreads = 8;

	FRDGPassRef lastPass = nullptr;
	uint32		iterIndex = 0;
	float		offsetFactor = 0.0;
	uint8		isDownSampling : 1;

	//FVector2f srcTexelSize;
	//FVector2f dstTexelSize;

	//FIntPoint srcTexSize;
	FIntPoint dstTexExtent;

	FRDGTextureRef srcTex;
	FRDGTextureRef dstTex;

public:
	void create(FRDGPassRef lastPass_, uint32 iterIndex_, float offsetFactor_, FRDGTextureRef srcTex_, bool isDownSampling_);

public:
	void getDstTextureNameTo(FString & out) const;
	void getPassNameTo(FString& out) const;
	FRDGEventName getRdgEventName() const;
};

struct FursDualKawaseBlurParams_Pipeline
{
	const FSceneView*						sceneView;
	FursDualKawaseBlurConfigs				configs;
	FursDualKawaseBlurParams_SamplingPass	samplingPassParams;

	FRDGTextureRef inputTex;
	FRDGTextureRef blurredTex;
};

/*
* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
*/
BEGIN_SHADER_PARAMETER_STRUCT(FursDualKawaseBlurParams_CS, )

	SHADER_PARAMETER(float, m_offsetFactor)

	SHADER_PARAMETER(FVector2f, m_srcTexelSize)
	SHADER_PARAMETER(FVector2f, m_dstTexelSize)
	SHADER_PARAMETER(FVector2f, m_dstTexExtent)

	SHADER_PARAMETER_SAMPLER(SamplerState,					m_srcTexSampler)
	SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>,		m_srcTex)
	SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>,	m_dstTex)

END_SHADER_PARAMETER_STRUCT()

/*
* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
*/
#if 1
BEGIN_SHADER_PARAMETER_STRUCT(FursDualKawaseBlurParams_GraphicsShader, )

	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters,	View)

	SHADER_PARAMETER_RDG_TEXTURE_SRV(Texture2D<float4>,			m_srcTex)
	SHADER_PARAMETER_SAMPLER(SamplerState,						m_srcTexSampler)

	RENDER_TARGET_BINDING_SLOTS()

END_SHADER_PARAMETER_STRUCT()
#endif // 0