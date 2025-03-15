# unrealsi1
unrealsi1 is a Unreal technical demo, currently focus on the rendering part. \
Also providing examples to use Unreal properly.

demo video: \
<a href="https://youtu.be/C87Qk5dcq7Y" target="_blank">
 <img src="doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_original.png" alt="unrealsi1_demo_video" width="512" height="256" />
</a>

**Table of Contents**
- Demos
- Features
- Technical Highlights
- Roadmap
- Requirement
- Build
- How to play
- References

## Requirement

- Unreal 5.4.4
- Visual Studio 2022

## Demos

### Render Features (C++ only, RDG, HLSL)
- dual kawase blur ([detail](doc/reference/render/feature/post_processing/dual_kawase_blur.md))

| original | 3 * 2 down/up sample | 4*2 down/up sample |
|---|---|---|
|![](doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_original.png)|![](doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_3+3.png)|![](doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_4+4.png)|


- simple particle system

| particles collision | debug with RenderDoc |
|---|---|
|![](doc/screenshot/render/feature/particle_system/simple_particle/simple_particle.jpg)|![](doc/screenshot/render/feature/particle_system/simple_particle/simple_particle_renderdoc.jpg)|

### Material Vfx (HLSL)

| dissovle | force field | simple water |
|---|---|---|
|![](doc/screenshot/render/material/vfx/dissolve.jpg)|![](doc/screenshot/render/material/vfx/force_field.jpg)|![](doc/screenshot/render/material/vfx/simple_water.jpg)
| world scanner | --- | --- |
|![](doc/screenshot/render/material/vfx/world_scanner.jpg)


## Features

- full HLSL integration for unreal material workflow (wip)
- unreal plugin and module examples


## Technical Highlights

- custom rendering pass by using Render Dependency Graph (RDG) and Compute Shader
- personal HLSL library by using unreal HLSL library instead of material nodes


## Roadmap

- rendering
  - anti-aliasing for procedure texture
  - more vfx
  - custom mesh pass, vertex factory

- tool
  - full hlsl integration for unreal material workflow
    - [ ] parse hlsl file
    - [ ] generate parameters for material
    - [ ] monitor file changes

- gameplay
	- simple character battle gameplay
		- [ ] character animation
		- [ ] damage system
		- [ ] ai behaviour


## Build

- open unrealsi1/unrealsi1.uproject

## How to play

- open unrealsi1/demo/test/render/feature for RDG feature
- open unrealsi1/demo/test/render/materual/vfx for material vfx

## References

please go to [reference](doc/reference/reference.md)