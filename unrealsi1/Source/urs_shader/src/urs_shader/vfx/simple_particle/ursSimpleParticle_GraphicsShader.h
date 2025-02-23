#pragma once

#include "urs_shader/common/urs_shader_common.h"

/*
* dumbass unreal cannot use prefix "_" as shader param, otherwise, it will recognize as a global param
*/

#if 1
BEGIN_SHADER_PARAMETER_STRUCT(FursSimpleParticleParams_GraphicsShader, )

	SHADER_PARAMETER_STRUCT_REF(FViewUniformShaderParameters, View)

	SHADER_PARAMETER(float,			m_scale)
	SHADER_PARAMETER(FLinearColor,	m_color)
	SHADER_PARAMETER(FVector3f,		m_objPos)

	// SHADER_PARAMETER_RDG_TEXTURE( Texture2D<float4>,	m_tex)
	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float3>, m_particlePosition)
	SHADER_PARAMETER_RDG_BUFFER_SRV(StructuredBuffer<float2>, m_particleLifespan) // x: remain, y: total

	RENDER_TARGET_BINDING_SLOTS()
END_SHADER_PARAMETER_STRUCT()
#endif // 0

#if 0
#pragma mark --- FursSimpleParticle_GraphicsShader-Decl ---
#endif // 0
#if 1

// use FMeshMaterialShader for static mesh
class FursSimpleParticle_GraphicsShader : public FGlobalShader
{
public:
	//using FParameters = FursSimpleParticleParams_GraphicsShader;

	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return true;
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
