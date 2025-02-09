#pragma once

#include "urs_shader/common/urs_shader_common.h"

#if 0
#pragma mark --- FursSimpleParticle_GraphicsShader-Decl ---
#endif // 0
#if 1

class FursSimpleParticle_GraphicsShader : public FGlobalShader
{
	DECLARE_INLINE_TYPE_LAYOUT(FursSimpleParticle_GraphicsShader, NonVirtual);
public:

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		//OutEnvironment.SetDefine(TEXT("GRID_SUBDIVISION_X"), kGridSubdivisionX);
		//OutEnvironment.SetDefine(TEXT("GRID_SUBDIVISION_Y"), kGridSubdivisionY);
	}

public:
	BEGIN_SHADER_PARAMETER_STRUCT(FParameters, ) 
	END_SHADER_PARAMETER_STRUCT()

	FursSimpleParticle_GraphicsShader() = default;
	FursSimpleParticle_GraphicsShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		PixelUVSize.Bind(Initializer.ParameterMap, TEXT("PixelUVSize"));
		RadialDistortionCoefs.Bind(Initializer.ParameterMap, TEXT("RadialDistortionCoefs"));
		TangentialDistortionCoefs.Bind(Initializer.ParameterMap, TEXT("TangentialDistortionCoefs"));
		DistortedCameraMatrix.Bind(Initializer.ParameterMap, TEXT("DistortedCameraMatrix"));
		UndistortedCameraMatrix.Bind(Initializer.ParameterMap, TEXT("UndistortedCameraMatrix"));
		OutputMultiplyAndAdd.Bind(Initializer.ParameterMap, TEXT("OutputMultiplyAndAdd"));
	}

	void SetParameters(
		FRHIBatchedShaderParameters& BatchedParameters,
		const FIntPoint& DisplacementMapResolution)
	{
		FVector2f PixelUVSizeValue(
			1.f / float(DisplacementMapResolution.X), 1.f / float(DisplacementMapResolution.Y));

		SetShaderValue(BatchedParameters, PixelUVSize, PixelUVSizeValue);
		/*SetShaderValue(BatchedParameters, DistortedCameraMatrix, FVector4f(CompiledCameraModel.DistortedCameraMatrix));
		SetShaderValue(BatchedParameters, UndistortedCameraMatrix, FVector4f(CompiledCameraModel.UndistortedCameraMatrix));
		SetShaderValue(BatchedParameters, RadialDistortionCoefs, RadialDistortionCoefsValue);
		SetShaderValue(BatchedParameters, TangentialDistortionCoefs, TangentialDistortionCoefsValue);
		SetShaderValue(BatchedParameters, OutputMultiplyAndAdd, FVector2f(CompiledCameraModel.OutputMultiplyAndAdd));*/
	}

private:
	LAYOUT_FIELD(FShaderParameter, PixelUVSize);
	LAYOUT_FIELD(FShaderParameter, RadialDistortionCoefs);
	LAYOUT_FIELD(FShaderParameter, TangentialDistortionCoefs);
	LAYOUT_FIELD(FShaderParameter, DistortedCameraMatrix);
	LAYOUT_FIELD(FShaderParameter, UndistortedCameraMatrix);
	LAYOUT_FIELD(FShaderParameter, OutputMultiplyAndAdd);
};

#endif

#if 0
#pragma mark --- FursSimpleParticle_VS-Decl ---
#endif // 0
#if 1

class FursSimpleParticle_VS : public FursSimpleParticle_GraphicsShader
{
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_VS);
public:
	FursSimpleParticle_VS() = default;
	FursSimpleParticle_VS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FursSimpleParticle_GraphicsShader(Initializer)
	{

	}
};

#endif

#if 0
#pragma mark --- FursSimpleParticle_PS-Decl ---
#endif // 0
#if 1

class FursSimpleParticle_PS : public FursSimpleParticle_GraphicsShader
{
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_PS);
public:
	FursSimpleParticle_PS() = default;
	FursSimpleParticle_PS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FursSimpleParticle_GraphicsShader(Initializer)
	{

	}
};

#endif