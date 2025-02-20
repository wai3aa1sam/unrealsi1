#include "ursSimpleParticle.h"
#include "ursSimpleParticle_CS.h"
#include "ursSimpleParticle_GraphicsShader.h"

#include <GameFramework/GameUserSettings.h>

#include <ProceduralMeshComponent.h>
#include <Engine/StaticMesh.h>

template<class TO, class FROM>
UE::Math::TVector<TO>
FVector3_cast(const UE::Math::TVector<FROM>& v)
{
	return UE::Math::TVector<TO>{ static_cast<TO>(v.X), static_cast<TO>(v.Y), static_cast<TO>(v.Z) };
}

int roundUpToMultiple(int v, int n) {
	return (v + n - 1) / n * n;
}

#if 1


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
#pragma mark --- AursSimpleParticle-Impl ---
#endif // 0
#if 1

AursSimpleParticle::AursSimpleParticle()
{
	PrimaryActorTick.bCanEverTick = true;

	//UStaticMesh* mesh = nullptr;
	//URS_CDO_FINDER(mesh,	"StaticMesh'/Engine/BasicShapes/Cube.Cube''");

	ExampleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Example Mesh"));
	//ExampleMesh->SetStaticMesh(mesh);
	RootComponent = ExampleMesh;
}

void 
AursSimpleParticle::setupShaderParams(FursSimpleParticleParams& out, FursSimpleParticleParamsCache& outParamsCache, FursSimpleParticleRdgRscsRef& outRdgRscsRef
									, FRDGBuilder& rdgBuilder, const FursSimpleParticleConfigs& configs)
{
	URS_ASSERT(IsInRenderingThread());

	out.m_initVelocity			= configs.initVelocity;
	out.m_initVelocityVariant	= configs.initVelocityVariant;
	out.m_initLifespan			= configs.initLifespan;
	out.m_initLifespanVariant	= configs.initLifespanVariant;

	out.m_deltaTime	= configs.deltaTime;
	out.m_emitterPos	= configs.emitPosition;
	out.m_gravity		= configs.gravity;
	out.m_bounciness	= configs.bounciness;

	if (true) {
		auto planeNormal = configs.plane.TransformVectorNoScale(FVector3d::UpVector);
		planeNormal.Normalize();
		//FVector4f plane = FVector4f{ planeNormal.X, planeNormal.Y, planeNormal.Z, 1.0 };
		FVector4f plane = FVector4f{FVector3_cast<float>(planeNormal) , 1.0};

		plane.W = configs.plane.GetTranslation().Dot(planeNormal);
		out.m_colliderPlane = plane;
	}

	bool isCreateBuffer = false;
	isCreateBuffer = !outParamsCache.particlePositionBuffer;

	int roundUpParticleCount = roundUpToMultiple(configs.MaxParticleCount, configs.numThreads);

	if (isCreateBuffer)
	{
		outRdgRscsRef.particlePositionBuffer = createStructuredBufferWithUav(&out.m_particlePosition, rdgBuilder, TEXT("m_particlePosition"), sizeof(FVector3f), roundUpParticleCount);
		outRdgRscsRef.particleVelocityBuffer = createStructuredBufferWithUav(&out.m_particleVelocity, rdgBuilder, TEXT("m_particleVelocity"), sizeof(FVector3f), roundUpParticleCount);
		outRdgRscsRef.particleLifespanBuffer = createStructuredBufferWithUav(&out.m_particleLifespan, rdgBuilder, TEXT("m_particleLifespan"), sizeof(FVector2f), roundUpParticleCount);

		// TODO: init
		TArray<FVector3f> noises;
		noises.SetNum(configs.particleNoiseCount);
		for (size_t i = 0; i < configs.particleNoiseCount; i++)
		{
			noises[i] = FVector3_cast<float>(FMath::VRand());
		}
		outRdgRscsRef.particleNoiseBuffer	 = createStructuredBufferWithSrv(&out.m_particleNoise,	 rdgBuilder, TEXT("m_particleNoise"), noises);
	}
	else
	{
		outRdgRscsRef.particlePositionBuffer = registerExternalBufferWithUav(&out.m_particlePosition, rdgBuilder, outParamsCache.particlePositionBuffer);
		outRdgRscsRef.particleVelocityBuffer = registerExternalBufferWithUav(&out.m_particleVelocity, rdgBuilder, outParamsCache.particleVelocityBuffer);
		outRdgRscsRef.particleLifespanBuffer = registerExternalBufferWithUav(&out.m_particleLifespan, rdgBuilder, outParamsCache.particleLifespanBuffer);
		outRdgRscsRef.particleNoiseBuffer	 = registerExternalBufferWithSrv(&out.m_particleNoise,	  rdgBuilder, outParamsCache.particleNoiseBuffer);
	}
}

void 
AursSimpleParticle::BeginPlay()
{
	Super::BeginPlay();

	GEngine->GameUserSettings->SetFrameRateLimit(60);

	_simpleParticleSvExt = FSceneViewExtensions::NewExtension<FursSimpleParticleSceneViewExt>(this);

	#if 0
	if (auto* world = GetWorld())
	{
		world->GetSubsystem<UursSimpleParticleSubSystem>()->setSimpleParticle(this);
	}
	#endif // 0
}

void 
AursSimpleParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto& configs = _configs;

	configs.emitPerSecond += DeltaTime * configs.emitPerSecond;
	configs.deltaTime = DeltaTime * configs.timeScale;

	int newParticleCount = static_cast<int>(configs.emitPerSecondRemain);
	configs.emitPerSecondRemain -= newParticleCount;

	int newParticleStart = configs.m_particleIndex;
	int newParticleEnd   = (configs.m_particleIndex + newParticleCount) % configs.MaxParticleCount;

	configs.m_particleIndex += newParticleCount;
	configs.m_particleIndex %= configs.MaxParticleCount;
	configs.m_activeParticleCount = FMath::Max(configs.m_particleIndex, configs.m_activeParticleCount);

	int threadGroup = (configs.m_activeParticleCount + configs.numThreads - 1) / configs.numThreads;
	if (threadGroup <= 0) return;

	//enqueueRenderCommand(RenderTarget, vertices);
}

void 
AursSimpleParticle::enqueueRenderCommand(const FSceneView& sceneView)
{
	//TShaderMapRef<FursSimpleParticle_CS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	bool isInvalidMesh = !_mesh || !_mesh->GetRenderData() || _mesh->GetRenderData()->LODResources.IsEmpty();
	if (isInvalidMesh)
		return;

	ENQUEUE_RENDER_COMMAND(ComputeShader)(
		[/*ComputeShader, */this, configs = _configs, &paramCache = _paramCache, sceneView = sceneView]
		(FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder rdgBuilder(RHICmdList);
			FursSimpleParticleRdgRscsRef rdgRscsRef;
			addSimulateParticlePass(rdgBuilder, rdgRscsRef, configs);
			addRenderParticlePass(rdgBuilder, sceneView, rdgRscsRef, configs);
		}
	);

}

void 
AursSimpleParticle::addSimulateParticlePass(FRDGBuilder& rdgBuilder, FursSimpleParticleRdgRscsRef& outRdgRscsRef, const FursSimpleParticleConfigs& configs)
{
	//RDG_CSV_STAT_EXCLUSIVE_SCOPE(GraphBuilder, RenderBasePass);
	//SCOPED_NAMED_EVENT(FDeferredShadingSceneRenderer_RenderBasePass, FColor::Emerald);

	int threadGroup = (configs.m_activeParticleCount + configs.numThreads - 1) / configs.numThreads;
	if (threadGroup <= 0)
		return;

	#if 1
	auto* params = rdgBuilder.AllocParameters<FursSimpleParticle_CS::FParameters>();
	URS_ASSERT(params);
	this->setupShaderParams(*params, this->_paramCache, outRdgRscsRef, rdgBuilder, configs);

	TShaderMapRef<FursSimpleParticle_CS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("SimpleParticle_CS_Simulate"), ComputeShader, params, FIntVector(threadGroup, 1, 1));
	#endif // 0
}

// build a quad mesh (vtx, idx buffer)
// vertex factory? GetVertexElements? vertex param?
// instanced draw
// how to add this pass to AfterRenderingTransparents
// init compute buffer

void 
AursSimpleParticle::addRenderParticlePass(FRDGBuilder& rdgBuilder, const FSceneView& sceneView, FursSimpleParticleRdgRscsRef& rdgRscsRef, const FursSimpleParticleConfigs& configs)
{
	auto& rhiCmdList = rdgBuilder.RHICmdList;

	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_BasePass));
	//RenderBasePassInternal(GraphBuilder, InViews, SceneTextures, BasePassRenderTargets, BasePassDepthStencilAccess, ForwardBasePassTextures, DBufferTextures, bDoParallelBasePass, bRenderLightmapDensity, InstanceCullingManager, bNaniteEnabled, NaniteBasePassShadingCommands, NaniteRasterResults);
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_AfterBasePass));

	// if (SubmitDrawBegin(MeshDrawCommand, GraphicsMinimalPipelineStateSet, SceneArgs, InstanceFactor, RHICmdList, StateCache, bAllowSkipDrawCommand))
	// AddSimpleMeshPass(

	#if 1
	FGlobalShaderMap* shaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FursSimpleParticle_VS> vs{shaderMap};
	TShaderMapRef<FursSimpleParticle_PS> ps{shaderMap};

	auto* shaderParams = rdgBuilder.AllocParameters<FursSimpleParticle_VS::FParameters>();

	rdgBuilder.AddPass(RDG_EVENT_NAME("RenderParticlePass"), ERDGPassFlags::Raster,
		[vs, ps, shaderParams, mesh = this->_mesh, configs = configs, sceneView = &sceneView]
		(FRHICommandList& rhiCmdList)
		{
			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			rhiCmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.DepthStencilState						= TStaticDepthStencilState<false, CF_Always>::GetRHI();
			GraphicsPSOInit.BlendState								= TStaticBlendState<>::GetRHI();
			GraphicsPSOInit.RasterizerState							= TStaticRasterizerState<>::GetRHI();
			GraphicsPSOInit.PrimitiveType							= PT_TriangleList;
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= GetVertexDeclarationFVector4();		// TODO: need modify
			GraphicsPSOInit.BoundShaderState.VertexShaderRHI		= vs.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI			= ps.GetPixelShader();
			SetGraphicsPipelineState(rhiCmdList, GraphicsPSOInit, 0);

			float depthMaxDefault = 1.0;

			
			//UStaticMesh* mesh = nullptr;
			//mesh->GetSourceModel(0).loa

			//RHICmdList.SetViewport(View.ViewRect.Min.X, View.ViewRect.Min.Y, 0, View.ViewRect.Max.X, View.ViewRect.Max.Y, 1);
			//OutTextureRenderTargetResource->GetSizeX(), OutTextureRenderTargetResource->GetSizeY(), 1.f);

			//sceneView.view;
			//rhiCmdList.SetViewport(0, 0, 0.f, OutTextureRenderTargetResource->GetSizeX(), OutTextureRenderTargetResource->GetSizeY(), depthMaxDefault);

			// SetShaderParameters(RHICmdList, PixelShader, PixelShader.GetPixelShader(), PixelParameters);

			//UProceduralMeshComponent* proceduralMeshComp = nullptr;
			//proceduralMeshComp->UpdateMeshSection

			SetShaderParameters(rhiCmdList, vs, vs.GetVertexShader(),	*shaderParams);
			SetShaderParameters(rhiCmdList, ps, ps.GetPixelShader(),	*shaderParams);

			#if 1
			auto* rdData = mesh->GetRenderData();
			auto& idxBuf = rdData->LODResources[0].IndexBuffer;

			FMeshDrawCommand cmd;
			mesh->GetRenderData()->LODVertexFactories[0].VertexFactory.GetStreams(GMaxRHIFeatureLevel, EVertexInputStreamType::Default, cmd.VertexStreams);
			cmd.IndexBuffer = idxBuf.IndexBufferRHI;

			auto vtxCount = mesh->GetRenderData()->LODResources[0].GetNumVertices();

			//const int8 PrimitiveIdStreamIndex = (IsUniformBufferStaticSlotValid(SceneArgs.BatchedPrimitiveSlot) ? -1 : MeshDrawCommand.PrimitiveIdStreamIndex);
			for (int32 VertexBindingIndex = 0; VertexBindingIndex < cmd.VertexStreams.Num(); VertexBindingIndex++)
			{
				const FVertexInputStream& Stream = cmd.VertexStreams[VertexBindingIndex];
				rhiCmdList.SetStreamSource(Stream.StreamIndex, Stream.VertexBuffer, Stream.Offset);
				//StateCache.VertexStreams[Stream.StreamIndex] = Stream;
			}
			//MeshDrawCommand.ShaderBindings.SetOnCommandList(RHICmdList, MeshPipelineState.BoundShaderState.AsBoundShaderState(), StateCache.ShaderBindings);

			auto primitiveCount = vtxCount / 3;
			auto instCount = configs.m_activeParticleCount;
			rhiCmdList.DrawIndexedPrimitive(cmd.IndexBuffer, 0, 0, vtxCount, 0, primitiveCount, instCount);
			#endif // 1
		}
	);
	#endif // 1
}

void 
AursSimpleParticle::createQuad(UStaticMesh* o)
{
	URS_ASSERT(o);

	auto* rdData = o->GetRenderData();

	if (rdData && !rdData->LODResources.IsEmpty())
	{
		auto& rsc = rdData->LODResources[0];

		//rsc.VertexBuffers.
	}
}

#endif
