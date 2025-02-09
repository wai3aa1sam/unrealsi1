#include "ursSimpleParticle_CS.h"
#include "ursSimpleParticle.h"

IMPLEMENT_GLOBAL_SHADER(FursSimpleParticle_CS, "/urs_shader/vfx/simple_particle/ursSimpleParticle_CS.usf", "CS_main", SF_Compute);

IMPLEMENT_GLOBAL_SHADER_PARAMETER_STRUCT(FursSimpleParticleParams, "FursSimpleParticleParams");

#if 0
#pragma mark --- FursSimpleParticle_CS-Impl ---
#endif // 0
#if 1

//void 
//FursSimpleParticle_CS::setupShaderParams(FParameters& out, const SimpleParticleConfigs& configs)
//{
//	out.initVelocity			= configs.initVelocity;
//	out.initVelocityVariant		= configs.initVelocityVariant;
//	out.initLifespan			= configs.initLifespan;
//	out.initLifespanVariant		= configs.initLifespanVariant;
//}

void
FursSimpleParticle_CS::BuildAndExecuteGraph(FRHICommandListImmediate &RHICmdList, UTextureRenderTarget2D* RenderTarget, const TArray<FVector3f>& InVerts)
{
	check(IsInRenderingThread());

	FRDGBuilder GraphBuilder(RHICmdList);

	auto* shaderParams = GraphBuilder.AllocParameters<FursSimpleParticle_CS::FParameters>();
	//shaderParams->

	auto& arr = InVerts;
	// --- Creating an SRV filled with vertex data ---
	// 1. Create a structured buffer
	FRDGBufferRef VerticesBuffer = CreateStructuredBuffer(
		GraphBuilder,
		TEXT("Vertices_StructuredBuffer"),
		sizeof(FVector3f),
		arr.Num(),
		arr.GetData(),
		sizeof(FVector3f) * arr.Num()
	);
	// 2. Create an RDG-tracked SRV from our structured buffer
	FRDGBufferSRVRef VerticesSRV = GraphBuilder.CreateSRV(VerticesBuffer, PF_R32_UINT);		// PF_R32_FLOAT is wrong
	//FRDGBufferSRVRef VerticesSRV = GraphBuilder.CreateSRV(VerticesBuffer, PF_R32G32B32F);

	// 3. Set our pass params
	//PassParameters->Vertices = VerticesSRV;

	// --- Creating a texture for the compute shader to write to ---
	// 1. Make a texture description 
	FRDGTextureDesc OutTextureDesc = FRDGTextureDesc::Create2D(
		FIntPoint(RenderTarget->SizeX, RenderTarget->SizeY),
		PF_FloatRGBA,
		FClearValueBinding(),
		TexCreate_UAV,
		1,
		1); 
	// 2. Allocate memory with above desc and get a ref to it
	FRDGTextureRef OutTextureRef = GraphBuilder.CreateTexture(OutTextureDesc, TEXT("Compute_Out_Texture"));
	// 3. Make a UAV description from our Texture Ref
	FRDGTextureUAVDesc OutTextureUAVDesc(OutTextureRef);
	// 4. Initialize it as our OutputTexture in our pass params
	//PassParameters->OutputTexture = GraphBuilder.CreateUAV(OutTextureUAVDesc);

	// ------ Add the compute pass ------
	// Get a reference to our global shader class
	TShaderMapRef<FursSimpleParticle_CS> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	// Add the compute shader pass to the render graph
	FComputeShaderUtils::AddPass(GraphBuilder, RDG_EVENT_NAME("Compute Pass"), ComputeShader, shaderParams, FIntVector(32, 32, 1));

	// ------ Extracting to pooled render target ------
	TRefCountPtr<IPooledRenderTarget> PooledComputeTarget;
	// Copy the result of compute shader from UAV to pooled renderT-target
	GraphBuilder.QueueTextureExtraction(OutTextureRef, &PooledComputeTarget);
	GraphBuilder.QueueBufferExtraction

	// Execute the graph
	GraphBuilder.Execute();

	FRHICopyTextureInfo copyInfo = {};
	// Queue the UAV we wrote to for extraction 
	RHICmdList.CopyTexture(PooledComputeTarget.GetReference()->GetRHI(), RenderTarget->GetRenderTargetResource()->TextureRHI, copyInfo);
}


#endif