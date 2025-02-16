#pragma once

#include "urs_shader/common/urs_shader_common.h"

struct	SimpleParticleConfigs;
class	AursSimpleParticle;

/*
* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
*/
BEGIN_SHADER_PARAMETER_STRUCT(FursSimpleParticleParams, )

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

#if 0
#pragma mark --- FursSimpleParticle_CS-Decl ---
#endif // 0
#if 1

class FursSimpleParticle_CS : public FGlobalShader
{
public:
	// DECLARE_EXPORTED_GLOBAL_SHADER(FursSimpleParticle_CS, URS_SHADER_API);
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_CS)
	SHADER_USE_PARAMETER_STRUCT(FursSimpleParticle_CS, FGlobalShader)

public:
	using FParameters = FursSimpleParticleParams;

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, GetMaxSupportedFeatureLevel(Parameters.Platform));
	}

	//void setupShaderParams(FParameters& out, const SimpleParticleConfigs& configs);

	//void addSimulatePass(FRDGBuilder& rdgBuilder, AursSimpleParticle* simpleParticle, const FursSimpleParticleConfigs& configs);
	void BuildAndExecuteGraph(FRHICommandListImmediate& RHICmdList, UTextureRenderTarget2D* RenderTarget, const TArray<FVector3f>& InVerts);
};

#endif