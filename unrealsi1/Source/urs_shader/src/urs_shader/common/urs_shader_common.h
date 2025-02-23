#pragma once

#define URS_SHADER_NAME_CSTR	"urs_shader"
#define URS_SHADER_ROOT_CSTR	"/urs_shader"

#define URS_MATERIAL_NAME_CSTR	"urs_material"
#define URS_MATERIAL_ROOT_CSTR	"/urs_material"

#include <CoreMinimal.h>

#include <urs_core.h>
#include <urs_core/render/urs_render.h>

#include <GlobalShader.h>
#include <ShaderParameterStruct.h>
#include <DataDrivenShaderPlatformInfo.h>

#include <RenderGraph.h>
#include <RenderTargetPool.h>
#include <Engine/TextureRenderTarget2D.h>

#include <Runtime/Renderer/Private/SceneRendering.h>
#include <MeshPassProcessor.h>
#include <SceneView.h>

#include <Runtime/Renderer/Public/FXRenderingUtils.h>