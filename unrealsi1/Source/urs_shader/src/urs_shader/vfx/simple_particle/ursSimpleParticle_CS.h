#pragma once

#include "urs_shader/common/urs_shader_common.h"

class SimpleParticleConfigs;


BEGIN_GLOBAL_SHADER_PARAMETER_STRUCT(FursSimpleParticleParams, )
	SHADER_PARAMETER(FVector3f, initVelocity)
	SHADER_PARAMETER(FVector3f, initVelocityVariant)

	SHADER_PARAMETER(float, initLifespan)
	SHADER_PARAMETER(float, initLifespanVariant)

	SHADER_PARAMETER(float, deltaTime)
	SHADER_PARAMETER(float, gravity)
	SHADER_PARAMETER(float, bounciness)

	SHADER_PARAMETER(FVector4f, ColliderPlane)
	SHADER_PARAMETER(FVector3f, emitterPos)

	SHADER_PARAMETER(int, m_activeParticleCount)
	SHADER_PARAMETER(int, newParticleStart)
	SHADER_PARAMETER(int, newParticleEnd)

	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float3>, _particleNoise)
	SHADER_PARAMETER(int, _particleNoiseCount)

	SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float3>, _particlePosition)
	SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float3>, _particleVelocity)
	SHADER_PARAMETER_RDG_BUFFER_UAV(RWStructuredBuffer<float2>, _particleLifespan) // x: remain, y: total
END_GLOBAL_SHADER_PARAMETER_STRUCT()

#if 0
#pragma mark --- FursSimpleParticle_CS-Decl ---
#endif // 0
#if 1

class FursSimpleParticle_CS : public FGlobalShader
{
private:
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_CS)
	SHADER_USE_PARAMETER_STRUCT(FursSimpleParticle_CS, FGlobalShader)

public:
	using FParameters = FursSimpleParticleParams;

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	//void setupShaderParams(FParameters& out, const SimpleParticleConfigs& configs);

	void BuildAndExecuteGraph(FRHICommandListImmediate& RHICmdList, UTextureRenderTarget2D* RenderTarget, const TArray<FVector3f>& InVerts);
};

#endif