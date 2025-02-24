#pragma once

#include "ursSimpleParticle_Common.h"

#if 0
#pragma mark --- FursSimpleParticle_CS-Decl ---
#endif // 0
#if 1

class FursSimpleParticle_CS : public FGlobalShader
{
public:
	// DECLARE_EXPORTED_GLOBAL_SHADER(FursSimpleParticle_CS, URS_SHADER_API);
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_CS)
	SHADER_USE_PARAMETER_STRUCT(FursSimpleParticle_CS, FGlobalShader)

public:
	using FParameters = FursSimpleParticleParams_CS;

public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, GetMaxSupportedFeatureLevel(Parameters.Platform));
	}

public:
	void setupShaderParams(FParameters* outParams, FRDGBuilder& rdgBuilder, FursSimpleParticleParams_Pass& passParams);
};

#endif

#if 0
#pragma mark --- FursSimpleParticle_GraphicsShader-Decl ---
#endif // 0
#if 1

// use FMeshMaterialShader for static mesh
class FursSimpleParticle_GraphicsShader : public FGlobalShader
{
public:
	//using FParameters = FursSimpleParticleParams_GraphicsShader;

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
	FursSimpleParticle_GraphicsShader() = default;
	FursSimpleParticle_GraphicsShader(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		//BindForLegacyShaderParameters<FParameters>(this, Initializer.PermutationId, Initializer.ParameterMap, false);
		//.Bind(Initializer.ParameterMap, TEXT("_color"));
	}

public:
	//LAYOUT_FIELD(FShaderParameter, _color);
};

#endif

#if 0
#pragma mark --- FursSimpleParticle_VS-Decl ---
#endif // 0
#if 1

class URS_SHADER_API FursSimpleParticle_VS : public FursSimpleParticle_GraphicsShader
{
public:
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_VS);
	SHADER_USE_PARAMETER_STRUCT(FursSimpleParticle_VS, FursSimpleParticle_GraphicsShader);
	using FParameters = FursSimpleParticleParams_GraphicsShader;

public:
};

#endif

#if 0
#pragma mark --- FursSimpleParticle_PS-Decl ---
#endif // 0
#if 1

class URS_SHADER_API FursSimpleParticle_PS : public FursSimpleParticle_GraphicsShader
{
public:
	DECLARE_GLOBAL_SHADER(FursSimpleParticle_PS);
	SHADER_USE_PARAMETER_STRUCT(FursSimpleParticle_PS, FursSimpleParticle_GraphicsShader);
	using FParameters = FursSimpleParticleParams_GraphicsShader;

public:
};

#endif
