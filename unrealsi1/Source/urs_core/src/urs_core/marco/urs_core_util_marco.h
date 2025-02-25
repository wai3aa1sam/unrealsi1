#pragma once

#include "urs_core_marco_common.h"
#include "../common/ursTypeTraits_Common.h"

#define URS_ENGINE_VERSION_5_5_OR_HIGHER                                           \
  (ENGINE_MAJOR_VERSION > 5 || ENGINE_MINOR_VERSION >= 5)

#define URS_ENGINE_VERSION_5_4_OR_HIGHER                                           \
  (ENGINE_MAJOR_VERSION > 5 || ENGINE_MINOR_VERSION >= 4)


#define URS_CDO_FINDER(outObj, assetpath) \
do \
{ \
	static ConstructorHelpers::FObjectFinder<ursRemoveAllPointer<typename decltype(outObj)> > finder(TEXT(assetpath)); \
	outObj = finder.Object; \
} \
while(false) \
// ---

#define URS_CDC_FINDER(outCls, assetpath) \
do \
{ \
	static ConstructorHelpers::FClassFinder<typename decltype(outCls)::ElementType> finder(TEXT(assetpath)); \
	outCls = finder.Class; \
} \
while(false) \
// ---