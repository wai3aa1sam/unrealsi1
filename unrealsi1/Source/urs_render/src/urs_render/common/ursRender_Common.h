#pragma once

#include "urs_core/common/urs_core_common.h"

#include <RenderGraph.h>

#define URS_GPU_PROFILE_SCOPE(rdgBuilder, var) RDG_GPU_STAT_SCOPE(rdgBuilder, var); RDG_EVENT_SCOPE(rdgBuilder, URS_STRINGIFY(var))

#if 0
#pragma mark --- AursRenderUtil-Decl ---
#endif // 0
#if 1



#endif