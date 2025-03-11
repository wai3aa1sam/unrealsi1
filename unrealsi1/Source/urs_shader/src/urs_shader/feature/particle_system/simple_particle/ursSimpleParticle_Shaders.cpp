#include "ursSimpleParticle_Shaders.h"
#include "ursSimpleParticle.h"

IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_CS, "/urs_shader/feature/particle_system/simple_particle/ursSimpleParticle_CS.usf",				"CS_main", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_VS, "/urs_shader/feature/particle_system/simple_particle/ursSimpleParticle_GraphicsShader.usf",	"VS_main", SF_Vertex);
IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_PS, "/urs_shader/feature/particle_system/simple_particle/ursSimpleParticle_GraphicsShader.usf",	"PS_main", SF_Pixel);

int roundUpToMultiple(int v, int n) {
	return (v + n - 1) / n * n;
}

#if 0
#pragma mark --- FursSimpleParticle_CS-Impl ---
#endif // 0
#if 1

void 
FursSimpleParticle_CS::setupShaderParams(FParameters* outParams, FRDGBuilder& rdgBuilder, FursSimpleParticleParams_Pass& passParams)
{
	URS_ASSERT(IsInRenderingThread());

	auto& out				= *outParams;
	auto& outRdgRscsRef		= passParams.rdgRscsRef;
	auto& outRdgRscsCache	= passParams.rdgRscsCache;

	const auto& configs = passParams.configs;
	out.m_initVelocity			= configs.initVelocity;
	out.m_initVelocityVariant	= configs.initVelocityVariant;
	out.m_initLifespan			= configs.initLifespan;
	out.m_initLifespanVariant	= configs.initLifespanVariant;

	out.m_emitterPos			= configs.emitPosition;
	out.m_gravity				= configs.gravity;
	out.m_bounciness			= configs.bounciness;

	out.m_deltaTime				= configs.deltaTime;
	out.m_activeParticleCount	= configs.activeParticleCount;
	out.m_newParticleStart		= configs.newParticleStart;
	out.m_newParticleEnd		= configs.newParticleEnd;
	out.m_particleNoiseCount	= configs.particleNoiseCount;

	if (true) {
		auto planeNormal = configs.plane.TransformVectorNoScale(FVector3d::UpVector);
		planeNormal.Normalize();
		//FVector4f plane = FVector4f{ planeNormal.X, planeNormal.Y, planeNormal.Z, 1.0 };
		//FVector4f plane = FVector4f{FVector3_cast<float>(planeNormal) , 1.0};
		FVector4f plane = FVector4f{FVector3f{planeNormal} , 1.0};

		plane.W = configs.plane.GetTranslation().Dot(planeNormal);
		out.m_colliderPlane = plane;
	}

	bool isCreateBuffer = false;
	isCreateBuffer = !outRdgRscsRef.particlePositionBuffer;

	if (isCreateBuffer)
	{
		int roundUpParticleCount = roundUpToMultiple(configs.maxParticleCount, configs.numThreads);

		outRdgRscsRef.particlePositionBuffer = ursRdgUtil::createStructuredBufferWithUav(&out.m_particlePosition, rdgBuilder, TEXT("ursParticlePositionBuffer"), sizeof(FVector3f), roundUpParticleCount);
		outRdgRscsRef.particleVelocityBuffer = ursRdgUtil::createStructuredBufferWithUav(&out.m_particleVelocity, rdgBuilder, TEXT("ursParticleVelocityBuffer"), sizeof(FVector3f), roundUpParticleCount);
		outRdgRscsRef.particleLifespanBuffer = ursRdgUtil::createStructuredBufferWithUav(&out.m_particleLifespan, rdgBuilder, TEXT("ursParticleLifespan"),		sizeof(FVector2f), roundUpParticleCount);

		TArray<FVector3f> noises;
		noises.SetNum(configs.particleNoiseCount);
		for (size_t i = 0; i < configs.particleNoiseCount; i++)
		{
			noises[i] = FVector3f{FMath::VRand()};
		}
		outRdgRscsRef.particleNoiseBuffer	 = ursRdgUtil::createStructuredBufferWithSrv(&out.m_particleNoise,	 rdgBuilder, TEXT("ursParticleNoise"), noises);
	}
	else
	{
		outRdgRscsRef.particlePositionBuffer = ursRdgUtil::registerExternalBufferWithUav(&out.m_particlePosition, rdgBuilder, outRdgRscsCache.particlePositionBuffer);
		outRdgRscsRef.particleVelocityBuffer = ursRdgUtil::registerExternalBufferWithUav(&out.m_particleVelocity, rdgBuilder, outRdgRscsCache.particleVelocityBuffer);
		outRdgRscsRef.particleLifespanBuffer = ursRdgUtil::registerExternalBufferWithUav(&out.m_particleLifespan, rdgBuilder, outRdgRscsCache.particleLifespanBuffer);
		outRdgRscsRef.particleNoiseBuffer	 = ursRdgUtil::registerExternalBufferWithSrv(&out.m_particleNoise,	  rdgBuilder, outRdgRscsCache.particleNoiseBuffer);
	}

	outRdgRscsCache.particlePositionBuffer	= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particlePositionBuffer);
	outRdgRscsCache.particleVelocityBuffer	= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particleVelocityBuffer);
	outRdgRscsCache.particleLifespanBuffer	= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particleLifespanBuffer);
	outRdgRscsCache.particleNoiseBuffer		= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particleNoiseBuffer);
}

#endif


