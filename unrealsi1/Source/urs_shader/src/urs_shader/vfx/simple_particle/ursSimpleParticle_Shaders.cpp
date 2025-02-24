#include "ursSimpleParticle_Shaders.h"
#include "ursSimpleParticle.h"

IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_CS, "/urs_shader/vfx/simple_particle/ursSimpleParticle_CS.usf",				"CS_main", SF_Compute);
IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_VS, "/urs_shader/vfx/simple_particle/ursSimpleParticle_GraphicsShader.usf",	"VS_main", SF_Vertex);
IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_PS, "/urs_shader/vfx/simple_particle/ursSimpleParticle_GraphicsShader.usf",	"PS_main", SF_Pixel);

int roundUpToMultiple(int v, int n) {
	return (v + n - 1) / n * n;
}

#if 1

struct ursRdgUtil
{
public:
	template<class T, class TAlloc>
	FRDGBufferRef createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);
	FRDGBufferRef createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);

	template<class T, class TAlloc>
	FRDGBufferRef createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);
	FRDGBufferRef createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None);

	FRDGBufferRef registerExternalBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf);
	FRDGBufferRef registerExternalBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf);
};

template<class T, class TAlloc>
FRDGBufferRef createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	// using ElementType = decltype(data)::ElementType;
	FRDGBufferRef buf = CreateStructuredBuffer(rdgBuilder, name, data, InitialDataFlags);
	FRDGBufferSRVRef bufSrv = rdgBuilder.CreateSRV(buf, PF_R32_UINT);
	*outSrv = bufSrv;
	return buf;
}

FRDGBufferRef createStructuredBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	FRDGBufferDesc desc = FRDGBufferDesc::CreateStructuredDesc(elementByteSize, elementCount);
	//*outBuf = rdgBuilder.CreateBuffer(desc, name);

	FRDGBufferRef buf = rdgBuilder.CreateBuffer(desc, name);
	*outSrv = rdgBuilder.CreateSRV(buf);
	return buf;
}

template<class T, class TAlloc>
FRDGBufferRef createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, TAlloc>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	// using ElementType = decltype(data)::ElementType;
	FRDGBufferRef buf = CreateStructuredBuffer(rdgBuilder, name, data, InitialDataFlags);
	FRDGBufferUAVRef bufUav = rdgBuilder.CreateUAV(buf, PF_R32_UINT);
	*outUav = bufUav;
	return buf;
}

FRDGBufferRef createStructuredBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	FRDGBufferDesc desc = FRDGBufferDesc::CreateStructuredDesc(elementByteSize, elementCount);
	//*outBuf = rdgBuilder.CreateBuffer(desc, name);

	FRDGBufferRef buf = rdgBuilder.CreateBuffer(desc, name);
	*outUav = rdgBuilder.CreateUAV(buf);
	return buf;
}

FRDGBufferRef registerExternalBufferWithUav(FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf)
{
	auto* buf = rdgBuilder.RegisterExternalBuffer(pooledBuf);
	*outUav = rdgBuilder.CreateUAV(buf);
	return buf;
}

FRDGBufferRef registerExternalBufferWithSrv(FRDGBufferSRV** outSrv, FRDGBuilder& rdgBuilder, TRefCountPtr<FRDGPooledBuffer>& pooledBuf)
{
	auto* buf = rdgBuilder.RegisterExternalBuffer(pooledBuf);
	*outSrv = rdgBuilder.CreateSRV(buf);
	return buf;
}

#endif // 1

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

		outRdgRscsRef.particlePositionBuffer = createStructuredBufferWithUav(&out.m_particlePosition, rdgBuilder, TEXT("simpPtcParticlePositionBuffer"), sizeof(FVector3f), roundUpParticleCount);
		outRdgRscsRef.particleVelocityBuffer = createStructuredBufferWithUav(&out.m_particleVelocity, rdgBuilder, TEXT("simpPtcParticleVelocityBuffer"), sizeof(FVector3f), roundUpParticleCount);
		outRdgRscsRef.particleLifespanBuffer = createStructuredBufferWithUav(&out.m_particleLifespan, rdgBuilder, TEXT("simpPtcParticleLifespan"),		sizeof(FVector2f), roundUpParticleCount);

		TArray<FVector3f> noises;
		noises.SetNum(configs.particleNoiseCount);
		for (size_t i = 0; i < configs.particleNoiseCount; i++)
		{
			noises[i] = FVector3f{FMath::VRand()};
		}
		outRdgRscsRef.particleNoiseBuffer	 = createStructuredBufferWithSrv(&out.m_particleNoise,	 rdgBuilder, TEXT("simpPtcParticleNoise"), noises);
	}
	else
	{
		outRdgRscsRef.particlePositionBuffer = registerExternalBufferWithUav(&out.m_particlePosition, rdgBuilder, outRdgRscsCache.particlePositionBuffer);
		outRdgRscsRef.particleVelocityBuffer = registerExternalBufferWithUav(&out.m_particleVelocity, rdgBuilder, outRdgRscsCache.particleVelocityBuffer);
		outRdgRscsRef.particleLifespanBuffer = registerExternalBufferWithUav(&out.m_particleLifespan, rdgBuilder, outRdgRscsCache.particleLifespanBuffer);
		outRdgRscsRef.particleNoiseBuffer	 = registerExternalBufferWithSrv(&out.m_particleNoise,	  rdgBuilder, outRdgRscsCache.particleNoiseBuffer);
	}

	outRdgRscsCache.particlePositionBuffer	= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particlePositionBuffer);
	outRdgRscsCache.particleVelocityBuffer	= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particleVelocityBuffer);
	outRdgRscsCache.particleLifespanBuffer	= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particleLifespanBuffer);
	outRdgRscsCache.particleNoiseBuffer		= rdgBuilder.ConvertToExternalBuffer(outRdgRscsRef.particleNoiseBuffer);
}

#endif


