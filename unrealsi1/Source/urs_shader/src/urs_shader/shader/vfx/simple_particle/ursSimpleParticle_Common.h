#pragma once

#include "urs_shader/common/urs_shader_common.h"
#include "urs_shader/shader/ursGlobalShader.h"

#include "ursSimpleParticle_Common.generated.h"

USTRUCT()
struct URS_SHADER_API FursSimpleParticleConfigs
{
	GENERATED_BODY()
public:
	static constexpr int numThreads = 64;
	static constexpr int particleNoiseCount = 2048;

public:
	UPROPERTY(EditAnywhere) int maxParticleCount = 10000;

	UPROPERTY(EditAnywhere) FVector3f initVelocity			= FVector3f(0, 0, 48);
	UPROPERTY(EditAnywhere) FVector3f initVelocityVariant	= FVector3f(24, 24, 16);

	UPROPERTY(EditAnywhere) float initLifespan = 15;
	UPROPERTY(EditAnywhere) float initLifespanVariant = 4;

	UPROPERTY(EditAnywhere) float emitPerSecond = 1000;
	UPROPERTY(EditAnywhere) float gravity		= -9.8f;
	UPROPERTY(EditAnywhere) float timeScale		= 2;
	UPROPERTY(EditAnywhere) float bounciness	= 0.75f;

	UPROPERTY(EditAnywhere)	FVector3f		emitPosition;
	UPROPERTY(EditAnywhere)	FTransform		plane;

	UPROPERTY(EditAnywhere)	float					scale	= 1.0f;
	UPROPERTY(EditAnywhere)	FLinearColor			color	= FLinearColor::Red;
	UPROPERTY(EditAnywhere)	TObjectPtr<UTexture2D>	texture = nullptr;

	// ---
	UPROPERTY(VisibleAnywhere) float	deltaTime				= 0;
	UPROPERTY(VisibleAnywhere) int		newParticleStart		= 0;
	UPROPERTY(VisibleAnywhere) int		newParticleEnd			= 0;
	UPROPERTY(VisibleAnywhere) float	emitPerSecondRemain		= 0;

	UPROPERTY(VisibleAnywhere) int		activeParticleCount		= 0;
	UPROPERTY(VisibleAnywhere) int		particleIndex			= 0;

public:
	int		getThreadGroup()	const { return (activeParticleCount + numThreads - 1) / numThreads; }
	bool	isValid()			const { return getThreadGroup() > 0; }
};

struct FursSimpleParticleRdgRscsCache
{
	TRefCountPtr<FRDGPooledBuffer> particlePositionBuffer	= nullptr;
	TRefCountPtr<FRDGPooledBuffer> particleVelocityBuffer	= nullptr;
	TRefCountPtr<FRDGPooledBuffer> particleLifespanBuffer	= nullptr;
	TRefCountPtr<FRDGPooledBuffer> particleNoiseBuffer		= nullptr;
};

struct FursSimpleParticleRdgRscsRef
{
	FRDGBufferRef particlePositionBuffer	= nullptr;
	FRDGBufferRef particleVelocityBuffer	= nullptr;
	FRDGBufferRef particleLifespanBuffer	= nullptr;
	FRDGBufferRef particleNoiseBuffer		= nullptr;
};

struct FursSimpleParticleParams_Pass
{
	const FSceneView*				sceneView;
	FursSimpleParticleConfigs		configs;
	FursSimpleParticleRdgRscsRef	rdgRscsRef;
	FursSimpleParticleRdgRscsCache	rdgRscsCache;
};

/*
* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
*/
BEGIN_SHADER_PARAMETER_STRUCT(FursSimpleParticleParams_CS, )

	SHADER_PARAMETER(FVector3f, m_initVelocity)
	SHADER_PARAMETER(FVector3f, m_initVelocityVariant)

	SHADER_PARAMETER(float, m_initLifespan)
	SHADER_PARAMETER(float, m_initLifespanVariant)

	SHADER_PARAMETER(float, m_deltaTime)
	SHADER_PARAMETER(float, m_gravity)
	SHADER_PARAMETER(float, m_bounciness)

	SHADER_PARAMETER(FVector4f, m_colliderPlane)
	SHADER_PARAMETER(FVector3f, m_emitterPos)

	SHADER_PARAMETER(int, m_activeParticleCount)
	SHADER_PARAMETER(int, m_newParticleStart)
	SHADER_PARAMETER(int, m_newParticleEnd)
	SHADER_PARAMETER(int, m_particleNoiseCount)

	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float3>,	m_particleNoise)
	SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float3>, m_particlePosition)
	SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float3>, m_particleVelocity)
	SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float2>, m_particleLifespan) // x: remain, y: total

END_SHADER_PARAMETER_STRUCT()

/*
* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
*/
#if 1
BEGIN_SHADER_PARAMETER_STRUCT(FursSimpleParticleParams_GraphicsShader, )

	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)

	SHADER_PARAMETER(float,			m_scale)
	SHADER_PARAMETER(FLinearColor,	m_color)
	SHADER_PARAMETER(FVector3f,		m_objPos)
	SHADER_PARAMETER(FMatrix44f,	m_matrixView)

	SHADER_PARAMETER_TEXTURE(Texture2D,							m_tex)
	SHADER_PARAMETER_SAMPLER(SamplerState,						m_texSampler)
	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float3>,	m_particlePosition)
	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float2>,	m_particleLifespan) // x: remain, y: total

	RENDER_TARGET_BINDING_SLOTS()

END_SHADER_PARAMETER_STRUCT()
#endif // 0