#pragma once

/*
reference:
~ https://github.com/nfgrep/CustomComputeExample
*/

#include "urs_render/common/urs_render_common.h"

#include <GlobalShader.h>
#include <ShaderParameterStruct.h>
#include <DataDrivenShaderPlatformInfo.h>

// This is the class that represents our shader within the engine
// This class is associated with shader-code in the corresponding .cpp
class FtrgTestComputeShader : public FGlobalShader
{
public:
	using VertexType = FVector3f;

private:
	// DECLARE_EXPORTED_GLOBAL_SHADER(FtrgTestComputeShader, URS_RENDER_API);
	DECLARE_GLOBAL_SHADER(FtrgTestComputeShader)
	SHADER_USE_PARAMETER_STRUCT(FtrgTestComputeShader, FGlobalShader)


	/*
	* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
	*/
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, )
		SHADER_PARAMETER(FVector3f, vtx)
		SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float3>, Vertices)
		SHADER_PARAMETER_RDG_TEXTURE_UAV(RWTexture2D<float4>, OutputTexture)
	END_SHADER_PARAMETER_STRUCT()

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	void BuildAndExecuteGraph(FRHICommandListImmediate& RHICmdList, UTextureRenderTarget2D* RenderTarget, const TArray<VertexType>& InVerts);
};