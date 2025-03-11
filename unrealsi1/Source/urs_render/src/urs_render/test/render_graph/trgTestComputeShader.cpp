#include "trgTestComputeShader.h"

#include "RenderGraph.h"
#include "RenderTargetPool.h"
#include "Engine/TextureRenderTarget2D.h"

IMPLEMENT_GLOBAL_SHADER(FtrgTestComputeShader, "/urs_render/test/render_graph/trgTestComputeShader.usf", "MainCompute", SF_Compute);
//IMPLEMENT_SHADER_TYPE(, FtrgTestComputeShader, TEXT("/urs_test_plugin/trgTestComputeShader.usf"), TEXT("MainCompute"), SF_Compute);

void 
FtrgTestComputeShader::BuildAndExecuteGraph(FRHICommandListImmediate &RHICmdList, UTextureRenderTarget2D* RenderTarget, const TArray<VertexType>& InVerts)
{
	// Our main point of contant with the RDG
	// We will use this to add resources (buffers) and passes to the render-graph
	FRDGBuilder GraphBuilder(RHICmdList);

	// This is a pointer to the shader-parameters we declared in the .h
	FParameters* PassParameters;
	// We ask the RDG to allocate some memory for our shader-parameters
	PassParameters = GraphBuilder.AllocParameters<FtrgTestComputeShader::FParameters>();

	auto& arr = InVerts;
	// --- Creating an SRV filled with vertex data ---
	// 1. Create a structured buffer
	FRDGBufferRef VerticesBuffer = CreateStructuredBuffer(
		GraphBuilder,
		TEXT("Vertices_StructuredBuffer"),
		sizeof(VertexType),
		arr.Num(),
		arr.GetData(),
		sizeof(VertexType) * arr.Num()
	);
	// 2. Create an RDG-tracked SRV from our structured buffer
	FRDGBufferSRVRef VerticesSRV = GraphBuilder.CreateSRV(VerticesBuffer, PF_R32_UINT);		// PF_R32_FLOAT is wrong
	//FRDGBufferSRVRef VerticesSRV = GraphBuilder.CreateSRV(VerticesBuffer, PF_R32G32B32F);
	
	// 3. Set our pass params
	PassParameters->Vertices = VerticesSRV;

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
	PassParameters->OutputTexture = GraphBuilder.CreateUAV(OutTextureUAVDesc);

	// ------ Add the compute pass ------
	// Get a reference to our global shader class
	TShaderMapRef<FtrgTestComputeShader> ComputeShader(GetGlobalShaderMap(GMaxRHIFeatureLevel));
	// Add the compute shader pass to the render graph
	FComputeShaderUtils::AddPass(GraphBuilder, RDG_EVENT_NAME("Compute Pass"), ComputeShader, PassParameters, FIntVector(32, 32, 1));

	// ------ Extracting to pooled render target ------
	TRefCountPtr<IPooledRenderTarget> PooledComputeTarget;
	// Copy the result of compute shader from UAV to pooled renderT-target
	GraphBuilder.QueueTextureExtraction(OutTextureRef, &PooledComputeTarget);

	// Execute the graph
	GraphBuilder.Execute();

	FRHICopyTextureInfo copyInfo = {};
	// Queue the UAV we wrote to for extraction 
	RHICmdList.CopyTexture(PooledComputeTarget.GetReference()->GetRHI(), RenderTarget->GetRenderTargetResource()->TextureRHI, copyInfo);
}

