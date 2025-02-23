#include "ursSimpleParticle.h"
#include "ursSimpleParticle_CS.h"
#include "ursSimpleParticle_GraphicsShader.h"

#include <GameFramework/GameUserSettings.h>

#include <ProceduralMeshComponent.h>
#include <Engine/StaticMesh.h>

#include <MediaShaders.h>

// CoreMesh.h

inline FBufferRHIRef createQuad(FRHICommandListBase& rhiCmdList, bool isYAxisUp, float ULeft = 0.0f, float URight = 1.0f, float VTop = 0.0f, float VBottom = 1.0f)
{
	FRHIResourceCreateInfo CreateInfo(TEXT("TempMediaVertexBuffer"));
	FBufferRHIRef VertexBufferRHI = rhiCmdList.CreateVertexBuffer(sizeof(FMediaElementVertex) * 4, BUF_Volatile, CreateInfo);
	void* VoidPtr = rhiCmdList.LockBuffer(VertexBufferRHI, 0, sizeof(FMediaElementVertex) * 4, RLM_WriteOnly);

	FMediaElementVertex* Vertices = (FMediaElementVertex*)VoidPtr;

	if (isYAxisUp)
	{
		Vertices[0].Position.Set(-1.0f,  1.0f, 1.0, 1.0f); // Top Left
		Vertices[1].Position.Set( 1.0f,	 1.0f, 1.0, 1.0f); // Top Right
		Vertices[2].Position.Set(-1.0f, -1.0f, 1.0, 1.0f); // Bottom Left
		Vertices[3].Position.Set( 1.0f,	-1.0f, 1.0, 1.0f); // Bottom Right
	}
	else
	{
		Vertices[0].Position.Set(-1.0f, 1.0f,  1.0f, 1.0f); // Top Left
		Vertices[1].Position.Set( 1.0f,	1.0f,  1.0f, 1.0f); // Top Right
		Vertices[2].Position.Set(-1.0f, 1.0f, -1.0f, 1.0f); // Bottom Left
		Vertices[3].Position.Set( 1.0f,	1.0f, -1.0f, 1.0f); // Bottom Right
	}
	
	Vertices[0].TextureCoordinate.Set(ULeft, VTop);
	Vertices[1].TextureCoordinate.Set(URight, VTop);
	Vertices[2].TextureCoordinate.Set(ULeft, VBottom);
	Vertices[3].TextureCoordinate.Set(URight, VBottom);
	rhiCmdList.UnlockBuffer(VertexBufferRHI);

	return VertexBufferRHI;
}

template<class TO, class FROM>
UE::Math::TVector<TO>
FVector3_cast(const UE::Math::TVector<FROM>& v)
{
	return UE::Math::TVector<TO>{ static_cast<TO>(v.X), static_cast<TO>(v.Y), static_cast<TO>(v.Z) };
}

template<class TO, class FROM>
UE::Math::TVector4<TO>
FVector4_cast(const UE::Math::TVector4<FROM>& v)
{
	return UE::Math::TVector4<TO>{ static_cast<TO>(v.X), static_cast<TO>(v.Y), static_cast<TO>(v.Z), static_cast<TO>(v.W) };
}

template<class TO, class FROM>
UE::Math::TMatrix<TO>
FMatrix4_cast(const UE::Math::TMatrix<FROM>& v)
{
	UE::Math::TMatrix<TO> o;
	o.SetColumn(0, FVector4_cast(v.GetColumn(0)));
	o.SetColumn(1, FVector4_cast(v.GetColumn(1)));
	o.SetColumn(2, FVector4_cast(v.GetColumn(2)));
	o.SetColumn(3, FVector4_cast(v.GetColumn(3)));
	return o;
}

int roundUpToMultiple(int v, int n) {
	return (v + n - 1) / n * n;
}


struct ursRenderUtil
{
public:
	static const FViewInfo& getViewInfo_Unsafe(const FSceneView& view)
	{
		check(view.bIsViewInfo);
		return static_cast<const FViewInfo&>(view);
	}

	static FIntRect getRawViewRect_Unsafe(const FSceneView& view)
	{
		return getViewInfo_Unsafe(view).ViewRect;
	}

};

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

	out.m_emitterPos	= configs.emitPosition;
	out.m_gravity		= configs.gravity;
	out.m_bounciness	= configs.bounciness;

	out.m_deltaTime				= configs.deltaTime;
	out.m_activeParticleCount	= configs.m_activeParticleCount;
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
	isCreateBuffer = !outParamsCache.particlePositionBuffer;

	if (isCreateBuffer)
	{
		int roundUpParticleCount = roundUpToMultiple(configs.maxParticleCount, configs.numThreads);

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

	if (RootComponent)
	{
		configs.emitPosition = FVector3f(RootComponent->GetComponentLocation());
	}

	configs.deltaTime = DeltaTime * configs.timeScale;

	configs.emitPerSecondRemain += DeltaTime * configs.emitPerSecond;

	int newParticleCount = static_cast<int>(configs.emitPerSecondRemain);
	configs.emitPerSecondRemain -= newParticleCount;

	configs.newParticleStart	= configs.m_particleIndex;
	configs.newParticleEnd		= (configs.m_particleIndex + newParticleCount) % configs.maxParticleCount;

	configs.m_particleIndex += newParticleCount;
	configs.m_particleIndex %= configs.maxParticleCount;
	configs.m_activeParticleCount = FMath::Max(configs.m_particleIndex, configs.m_activeParticleCount);

	int threadGroup = (configs.m_activeParticleCount + configs.numThreads - 1) / configs.numThreads;
	if (threadGroup <= 0) return;

	_passParams.configs = configs;
	//enqueueRenderCommand(RenderTarget, vertices);
}

void 
AursSimpleParticle::RenderThread_render(FRDGBuilder& rdgBuilder, const FSceneView& sceneView)
{
	check(IsInRenderingThread());
	_passParams.sceneView = &sceneView;

	//TShaderMapRef<FursSimpleParticle_CS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));

	bool isInvalidMesh = !_mesh || !_mesh->GetRenderData() || _mesh->GetRenderData()->LODResources.IsEmpty();
	if (isInvalidMesh)
		return;

	#if 0
	ENQUEUE_RENDER_COMMAND(ComputeShader)(
		[this]
		(FRHICommandListImmediate& RHICmdList)
		{
			FRDGBuilder rdgBuilder(RHICmdList);
			FursSimpleParticleRdgRscsRef rdgRscsRef;
			addSimulateParticlePass(rdgBuilder, &_passParams);
			//addRenderParticlePass(rdgBuilder, &_passParams);
		}
	);
	#else
	addSimulateParticlePass(rdgBuilder, &_passParams);
	addRenderParticlePass(rdgBuilder, &_passParams);
	#endif // 0
}

void 
AursSimpleParticle::addSimulateParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams)
{
	//RDG_CSV_STAT_EXCLUSIVE_SCOPE(GraphBuilder, RenderBasePass);
	//SCOPED_NAMED_EVENT(FDeferredShadingSceneRenderer_RenderBasePass, FColor::Emerald);

	const auto& configs = passParams->configs;
	auto& outRdgRscsRef = passParams->rdgRscsRef;

	int threadGroup = (configs.m_activeParticleCount + configs.numThreads - 1) / configs.numThreads;
	if (threadGroup <= 0)
		return;

	#if 1
	auto* params = rdgBuilder.AllocParameters<FursSimpleParticle_CS::FParameters>();
	URS_ASSERT(params);
	this->setupShaderParams(*params, this->_paramCache, outRdgRscsRef, rdgBuilder, configs);

	TShaderMapRef<FursSimpleParticle_CS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	FComputeShaderUtils::AddPass(rdgBuilder, RDG_EVENT_NAME("SimulateParticlePass"), ComputeShader, params, FIntVector(threadGroup, 1, 1));
	#endif // 0
}

void 
AursSimpleParticle::addRenderParticlePass(FRDGBuilder& rdgBuilder, PassParams* passParams)
{
	auto& rhiCmdList	= rdgBuilder.RHICmdList;
	auto& sceneView		= *passParams->sceneView;
	auto& rdgRscsRef	= passParams->rdgRscsRef;

	if (!rdgRscsRef.particlePositionBuffer)
		return;

	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_BasePass));
	//RenderBasePassInternal(GraphBuilder, InViews, SceneTextures, BasePassRenderTargets, BasePassDepthStencilAccess, ForwardBasePassTextures, DBufferTextures, bDoParallelBasePass, bRenderLightmapDensity, InstanceCullingManager, bNaniteEnabled, NaniteBasePassShadingCommands, NaniteRasterResults);
	//GraphBuilder.SetCommandListStat(GET_STATID(STAT_CLM_AfterBasePass));

	// if (SubmitDrawBegin(MeshDrawCommand, GraphicsMinimalPipelineStateSet, SceneArgs, InstanceFactor, RHICmdList, StateCache, bAllowSkipDrawCommand))
	// AddSimpleMeshPass(

	#if 1
	FGlobalShaderMap* shaderMap = GetGlobalShaderMap(GMaxRHIFeatureLevel);
	TShaderMapRef<FursSimpleParticle_VS> vs{shaderMap};
	TShaderMapRef<FursSimpleParticle_PS> ps{shaderMap};

	auto* shaderParams = rdgBuilder.AllocParameters<FursSimpleParticle_PS::FParameters>();

	auto& viewInfo = ursRenderUtil::getViewInfo_Unsafe(sceneView);

	auto sceneTexs = viewInfo.GetSceneTextures();
	shaderParams->RenderTargets[0]				= FRenderTargetBinding(sceneTexs.Color.Target, ERenderTargetLoadAction::ELoad);
	shaderParams->RenderTargets.DepthStencil	= FDepthStencilBinding(sceneTexs.Depth.Target, ERenderTargetLoadAction::ELoad, FExclusiveDepthStencil::DepthWrite_StencilNop);

	shaderParams->View							= viewInfo.ViewUniformBuffer;
	shaderParams->m_color						= passParams->configs.color;
	shaderParams->m_scale						= passParams->configs.scale;
	shaderParams->m_matrixVp					= FMatrix44f{viewInfo.ViewMatrices.GetViewProjectionMatrix()};	// TODO: remove
	shaderParams->m_matrixView					= FMatrix44f{viewInfo.ViewMatrices.GetViewMatrix()};
	shaderParams->m_objPos						= passParams->configs.emitPosition;		// TODO: remove

	shaderParams->m_particlePosition			= rdgBuilder.CreateSRV(rdgRscsRef.particlePositionBuffer);
	shaderParams->m_particleLifespan			= rdgBuilder.CreateSRV(rdgRscsRef.particleLifespanBuffer);

	rdgBuilder.AddPass(RDG_EVENT_NAME("RenderParticlePass"), shaderParams, ERDGPassFlags::Raster,
		[vs, ps, shaderParams, mesh = this->_mesh, passParams, this]
		(FRHICommandList& rhiCmdList)
		{
			const auto& configs	= passParams->configs;
			auto& sceneView		= *passParams->sceneView;

			float depthMaxDefault = 1.0;

			const FIntRect viewRect = ursRenderUtil::getRawViewRect_Unsafe(sceneView);
			rhiCmdList.SetViewport(viewRect.Min.X, viewRect.Min.Y, 0.0f, viewRect.Max.X, viewRect.Max.Y, depthMaxDefault);

			FGraphicsPipelineStateInitializer GraphicsPSOInit;
			rhiCmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
			GraphicsPSOInit.bDepthBounds							= true;
			GraphicsPSOInit.DepthStencilAccess						= FExclusiveDepthStencil::DepthRead;
			GraphicsPSOInit.DepthStencilState						= TStaticDepthStencilState<false, CF_DepthNearOrEqual>::GetRHI();
			GraphicsPSOInit.BlendState								= TStaticBlendState<CW_RGBA, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha, BO_Add, BF_SourceAlpha, BF_InverseSourceAlpha>::GetRHI();
			GraphicsPSOInit.RasterizerState							= TStaticRasterizerState<>::GetRHI();
			GraphicsPSOInit.PrimitiveType							= PT_TriangleList;
			GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= GMediaVertexDeclaration.VertexDeclarationRHI; // GMediaVertexDeclaration.VertexDeclarationRHI; //GetVertexDeclarationFVector4();		// TODO: need modify
			//GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI	= mesh->GetRenderData()->LODVertexFactories[0].VertexFactory.GetDeclaration();

			GraphicsPSOInit.BoundShaderState.VertexShaderRHI		= vs.GetVertexShader();
			GraphicsPSOInit.BoundShaderState.PixelShaderRHI			= ps.GetPixelShader();
			SetGraphicsPipelineState(rhiCmdList, GraphicsPSOInit, 0);
			
			SetShaderParameters(rhiCmdList, vs, vs.GetVertexShader(),	*shaderParams);
			SetShaderParameters(rhiCmdList, ps, ps.GetPixelShader(),	*shaderParams);
			//SetShaderParametersLegacyVS(RHICmdList, VertexShader, InView);
			//SetShaderParametersLegacyPS(RHICmdList, PixelShader, InView, MaterialProxy, CameraMaterial);

			#if 0
			auto* rdData = mesh->GetRenderData();
			auto& idxBuf = rdData->LODResources[0].IndexBuffer;

			FMeshDrawCommand cmd;
			mesh->GetRenderData()->LODVertexFactories[0].VertexFactory.GetStreams(GMaxRHIFeatureLevel, EVertexInputStreamType::Default, cmd.VertexStreams);
			cmd.IndexBuffer = idxBuf.IndexBufferRHI;

			//const int8 PrimitiveIdStreamIndex = (IsUniformBufferStaticSlotValid(SceneArgs.BatchedPrimitiveSlot) ? -1 : MeshDrawCommand.PrimitiveIdStreamIndex);
			for (int32 VertexBindingIndex = 0; VertexBindingIndex < cmd.VertexStreams.Num(); VertexBindingIndex++)
			{
				const FVertexInputStream& Stream = cmd.VertexStreams[VertexBindingIndex];
				rhiCmdList.SetStreamSource(Stream.StreamIndex, Stream.VertexBuffer, Stream.Offset);
				//StateCache.VertexStreams[Stream.StreamIndex] = Stream;
			}
			//MeshDrawCommand.ShaderBindings.SetOnCommandList(RHICmdList, MeshPipelineState.BoundShaderState.AsBoundShaderState(), StateCache.ShaderBindings);

			auto vtxCount = mesh->GetRenderData()->LODResources[0].GetNumVertices();
			auto primitiveCount = vtxCount / 3;
			auto instCount = configs.m_activeParticleCount;
			//rhiCmdList.DrawIndexedPrimitive(cmd.IndexBuffer, 0, 0, vtxCount, 0, primitiveCount, instCount);
			rhiCmdList.DrawIndexedPrimitive(cmd.IndexBuffer, 0, 0, vtxCount, 0, primitiveCount, 1);

			#else

			#if 0

			FBufferRHIRef VertexBuffer = ::createQuad(rhiCmdList);
			rhiCmdList.SetStreamSource(0, VertexBuffer, 0);
			rhiCmdList.DrawPrimitive(0, 2, 1);

			#else

			//static const uint16 Indices[] = { 0, 1, 2, 0, 2, 3 };
			static const uint16 Indices[] = { 0, 2, 1, 1, 2, 3 };

			FRHIResourceCreateInfo CreateInfo(TEXT("quad_idxs"));
			FBufferRHIRef IndexBufferRHI = rhiCmdList.CreateIndexBuffer(sizeof(uint16), sizeof(uint16) * 6, BUF_Volatile, CreateInfo);
			void* VoidPtr2 = rhiCmdList.LockBuffer(IndexBufferRHI, 0, sizeof(uint16) * 6, RLM_WriteOnly);
			FPlatformMemory::Memcpy(VoidPtr2, Indices, sizeof(uint16) * 6);
			rhiCmdList.UnlockBuffer(IndexBufferRHI);

			FBufferRHIRef VertexBuffer = ::createQuad(rhiCmdList, this->tempIsYAxisUp);
			rhiCmdList.SetStreamSource(0, VertexBuffer, 0);
			rhiCmdList.DrawIndexedPrimitive(IndexBufferRHI, 0, 0, 4, 0, 2, configs.tempIsUseOverrideInstCount ? configs.overrideInstCount : configs.m_activeParticleCount);

			#endif // 0

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
