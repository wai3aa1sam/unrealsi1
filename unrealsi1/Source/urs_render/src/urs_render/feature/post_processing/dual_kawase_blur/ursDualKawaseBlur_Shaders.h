#pragma once

#include "ursDualKawaseBlur_Common.h"

#if 0
#pragma mark --- FursDualKawaseBlur_CS-Decl ---
#endif // 0
#if 1

class FursDualKawaseBlur_CS : public FursGlobalShader
{
public:
	using Super = FursGlobalShader;
	using FParameters = FursDualKawaseBlurParams_CS;

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, GetMaxSupportedFeatureLevel(Parameters.Platform));
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		//OutEnvironment.SetDefine(TEXT("URS_DKB_THREADS"), 1);
	}

public:
	FursDualKawaseBlur_CS() = default;
	FursDualKawaseBlur_CS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: Super(Initializer)
	{
	}

public:
	void createShaderParams(FParameters* outParams, FRDGBuilder& rdgBuilder, FursDualKawaseBlurParams_SamplingPass& passParams);
};

#endif

#if 0
#pragma mark --- FursDualKawaseBlur_DownSampling_CS-Decl ---
#endif // 0
#if 1

class FursDualKawaseBlur_DownSampling_CS : public FursDualKawaseBlur_CS
{
public:
	using Super = FursDualKawaseBlur_CS;
	using FParameters = FursDualKawaseBlurParams_CS;

	// DECLARE_EXPORTED_GLOBAL_SHADER(FursDualKawaseBlur_CS, URS_RENDER_API);
	DECLARE_GLOBAL_SHADER(FursDualKawaseBlur_DownSampling_CS)
	SHADER_USE_PARAMETER_STRUCT(FursDualKawaseBlur_DownSampling_CS, Super)

public:
	//void setupShaderParams(FParameters* outParams, FRDGBuilder& rdgBuilder, FursDualKawaseBlurParams_Pass& passParams);
};

#endif

#if 0
#pragma mark --- FursDualKawaseBlur_UpSampling_CS-Decl ---
#endif // 0
#if 1

class FursDualKawaseBlur_UpSampling_CS : public FursDualKawaseBlur_CS
{
public:
	using Super = FursDualKawaseBlur_CS;
	using FParameters = FursDualKawaseBlurParams_CS;

	// DECLARE_EXPORTED_GLOBAL_SHADER(FursDualKawaseBlur_CS, URS_RENDER_API);
	DECLARE_GLOBAL_SHADER(FursDualKawaseBlur_UpSampling_CS)
	SHADER_USE_PARAMETER_STRUCT(FursDualKawaseBlur_UpSampling_CS, Super)

public:
	//void setupShaderParams(FParameters* outParams, FRDGBuilder& rdgBuilder, FursDualKawaseBlurParams_Pass& passParams);
};

#endif


#if 0
#pragma mark --- FursDualKawaseBlur_GraphicsShader-Decl ---
#endif // 0
#if 1

// use FMeshMaterialShader for static mesh
class FursDualKawaseBlur_GraphicsShader : public FursGlobalShader
{
public:
	using Super = FursGlobalShader;
	//using FParameters = FursDualKawaseBlurParams_GraphicsShader;

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, GetMaxSupportedFeatureLevel(Parameters.Platform));
	}

	static void ModifyCompilationEnvironment(const FGlobalShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
	{
		FGlobalShader::ModifyCompilationEnvironment(Parameters, OutEnvironment);
		//OutEnvironment.SetDefine(TEXT("VF_SUPPORTS_PRIMITIVE_SCENE_DATA"), 1);
	}

public:
	FursDualKawaseBlur_GraphicsShader() = default;
	FursDualKawaseBlur_GraphicsShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: Super(Initializer)
	{
		//BindForLegacyShaderParameters<FParameters>(this, Initializer.PermutationId, Initializer.ParameterMap, false);
		//.Bind(Initializer.ParameterMap, TEXT("_color"));
	}

public:
	//LAYOUT_FIELD(FShaderParameter, _color);
};

#endif

#if 0
#pragma mark --- FursDualKawaseBlur_VS-Decl ---
#endif // 0
#if 1

class URS_RENDER_API FursDualKawaseBlur_VS : public FursDualKawaseBlur_GraphicsShader
{
public:
	DECLARE_GLOBAL_SHADER(FursDualKawaseBlur_VS);
	SHADER_USE_PARAMETER_STRUCT(FursDualKawaseBlur_VS, FursDualKawaseBlur_GraphicsShader);
	using FParameters = FursDualKawaseBlurParams_GraphicsShader;

public:
};

#endif

#if 0
#pragma mark --- FursDualKawaseBlur_PS-Decl ---
#endif // 0
#if 1

class URS_RENDER_API FursDualKawaseBlur_PS : public FursDualKawaseBlur_GraphicsShader
{
public:
	DECLARE_GLOBAL_SHADER(FursDualKawaseBlur_PS);
	SHADER_USE_PARAMETER_STRUCT(FursDualKawaseBlur_PS, FursDualKawaseBlur_GraphicsShader);
	using FParameters = FursDualKawaseBlurParams_GraphicsShader;

public:
};

#endif
