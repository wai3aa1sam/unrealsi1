#include "ursSimpleParticle.h"
#include "ursSimpleParticle_CS.h"
#include "ursSimpleParticle_GraphicsShader.h"

#include <GameFramework/GameUserSettings.h>

#if 0
#pragma mark --- AursSimpleParticle-Impl ---
#endif // 0
#if 1

AursSimpleParticle::AursSimpleParticle()
{
	PrimaryActorTick.bCanEverTick = true;

	UStaticMesh* mesh = nullptr;
	URS_CDO_FINDER(mesh,	"StaticMesh'/Engine/BasicShapes/Cube.Cube''");

	ExampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Example Mesh"));
	ExampleMesh->SetStaticMesh(mesh);
	RootComponent = ExampleMesh;
}

//template<class T, class ALLOC>
//FRDGBufferRef createBuffer(FRDGBuilder& rdgBuilder, const TArray<T, ALLOC>& data)
//{
//	using ElementType = decltype(data)::ElementType;
//
//	FRDGBufferRef bufPos = CreateStructuredBuffer(
//		rdgBuilder,
//		TEXT("particlePositions"),
//		sizeof(T),
//		data.Num(),
//		data.GetData(),
//		sizeof(T) * data.Num()
//	);
//
//	return 
//}

template<class T, class ALLOC>
void createStructuredBufferToSrv(FRDGBufferSRV*& out, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, ALLOC>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	// using ElementType = decltype(data)::ElementType;
	FRDGBufferRef buf = CreateStructuredBuffer(rdgBuilder, name, data, InitialDataFlags);
	FRDGBufferSRVRef bufSrv = rdgBuilder.CreateSRV(buf, PF_R32_UINT);
	out = bufSrv;
}

template<class T, class ALLOC>
void createStructuredBufferToUav(FRDGBufferUAV*& out, FRDGBuilder& rdgBuilder, const TCHAR* name, const TArray<T, ALLOC>& data, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	// using ElementType = decltype(data)::ElementType;
	FRDGBufferRef buf = CreateStructuredBuffer(rdgBuilder, name, data, InitialDataFlags);
	FRDGBufferUAVRef bufUav = rdgBuilder.CreateUAV(buf, PF_R32_UINT);
	out = bufUav;
}

void createStructuredBufferToUav(FRDGBufferRef& outBuf, FRDGBufferUAV** outUav, FRDGBuilder& rdgBuilder, const TCHAR* name, uint32 elementByteSize, uint32 elementCount, ERDGInitialDataFlags InitialDataFlags = ERDGInitialDataFlags::None)
{
	FRDGBufferDesc desc = FRDGBufferDesc::CreateStructuredDesc(elementByteSize, elementCount);
	*outBuf = rdgBuilder.CreateBuffer(desc, name);
	*outUav = rdgBuilder.CreateUAV(*outBuf);
}

void 
AursSimpleParticle::setupShaderParams(FursSimpleParticleParams& out, FursSimpleParticleParamCache& outParamCache
										, FRDGBuilder& rdgBuilder
										, const FursSimpleParticleConfigs& configs)
{
	URS_ASSERT(IsInRenderingThread());

	out.initVelocity			= configs.initVelocity;
	out.initVelocityVariant		= configs.initVelocityVariant;
	out.initLifespan			= configs.initLifespan;
	out.initLifespanVariant		= configs.initLifespanVariant;

	out.deltaTime = dt * configs.timeScale;
	out.emitterPos = position;
	out.gravity = configs.gravity;
	out.bounciness = configs.bounciness;

	/*FRDGBufferRef bufPos = CreateStructuredBuffer(rdgBuilder, TEXT("particlePositions"), resources.particlePositions);
	FRDGBufferSRVRef VerticesSRV = rdgBuilder.CreateSRV(bufPos, PF_R32_UINT);
	out._particlePosition = VerticesSRV;*/
	// createBufferToSrv(out._particlePosition,	rdgBuilder, TEXT("particlePosition"),	resources.particlePositions);
	// createBufferToSrv(out._particleVelocity,	rdgBuilder, TEXT("particleVelocity"),	resources.particleVelocities);
	// createBufferToSrv(out._particleLifespan,	rdgBuilder, TEXT("particleLifespan"),	resources.particleLifespans);
	// createBufferToSrv(out._particleNoise,		rdgBuilder, TEXT("particleNoise"),		resources.particleNoises);
	// out._particleNoiseCount = resources.particleNoiseCount;

	// UniformBufferParameters->IndirectionGridBuffer = GraphBuilder.CreateSRV(GraphBuilder.RegisterExternalBuffer(AdaptiveOrthoGridParameterCache.IndirectionGridBuffer));
	FRDGBufferRef buf;
	FRDGBufferSRVRef bufSrv = rdgBuilder.CreateSRV(buf);


	bool isCreateBuffer = false;
	isCreateBuffer = !paramCache.particlePositionBuffer;

	int roundUpParticleCount = RoundUpToMultiple(MaxParticleCount, numThreads);

	if (isCreateBuffer)
	{
		createStructuredBufferToUav(outParamCache.particlePositionBuffer.GetReference(), &out._particlePosition, rdgBuilder, TEXT("name"), sizeof(FVector3f), roundUpParticleCount);
		outParamCache.particlePositionBuffer = rdgBuilder.CreateBuffer(desc, name);

	}
	// createExternalBufferSrv
	//out._particlePosition = rdgBuilder.CreateSRV(rdgBuilder.RegisterExternalBuffer(paramCache.particlePositionBuffer));


	//out.m_activeParticleCount = configs.m_activeParticleCount;
	//out.newParticleStart = 
}

void 
AursSimpleParticle::BeginPlay()
{
	Super::BeginPlay();

	GEngine->GameUserSettings->SetFrameRateLimit(60);
}

void 
AursSimpleParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//auto vertices = getVertices(this);
	//if (vertices.Num() > 0)
	//{
	//	auto vertex = vertices[0];
	//	vertex.Normalize();

	//	URS_LOG_INLINE("urs_log: vertex: {}", vertex);
	//	//String str = FString::Printf(TEXT("- after normalize vertices[0]=[%f, %f, %f]"), vertex.X, vertex.Y, vertex.Z);
	//	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, str);
	//}
	//enqueueRenderCommand(RenderTarget, vertices);
}

void 
AursSimpleParticle::enqueueRenderCommand(UTextureRenderTarget2D* texRdt, const TArray<FVector3f>& Vertices)
{
	TShaderMapRef<FursSimpleParticle_CS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	UTextureRenderTarget2D* RenderTargetParam = texRdt;
	TArray<FVector3f> VerticesParam = Vertices;

	ENQUEUE_RENDER_COMMAND(ComputeShader)(
		[
			ComputeShader,
				RenderTargetParam,
				VerticesParam
		](FRHICommandListImmediate& RHICmdList)
		{
			ComputeShader->BuildAndExecuteGraph(
				RHICmdList,
				RenderTargetParam,
				VerticesParam);
		}
	);

}



#endif