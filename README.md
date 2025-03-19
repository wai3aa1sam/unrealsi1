# unrealsi1
unrealsi1 is a Unreal technical demo, currently focus on the rendering part.

## Demo video
<a href="https://youtu.be/C87Qk5dcq7Y" target="_blank">
 <img src="doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_original_play.png" alt="unrealsi1_demo_video" width="400" height="" />
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

- ## Dual Kawase Blur ([performance detail](doc/detail/render/feature/post_processing/dual_kawase_blur/dual_kawase_blur.md)) 
  2x speedup compare to unreal blur impl

  | original | 3 + 3 down/up sample | 4 + 4 down/up sample |
  |---|---|---|
  |![](doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_original.png)|![](doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_3+3.png)|![](doc/screenshot/render/feature/post_processing/dual_kawase_blur/dkBlur_4+4.png)|


- ## Simple Particle System

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




## Build

- open unrealsi1/unrealsi1.uproject

## How to play

- open unrealsi1/demo/test/render/feature for RDG feature
- open unrealsi1/demo/test/render/materual/vfx for material vfx

## Roadmap

please go to [roadmap](doc/detail/roadmap.md)

## References

please go to [reference](doc/reference/reference.md)