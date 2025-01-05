#pragma once

#include "../detect_platform/urs_detect_platform.h"
#include "../marco/urs_core_marco.h"

#include <CoreMinimal.h>
#include <Delegates/DelegateCombinations.h>

#include "ursLog.h"
#include "ursTypeTraits_Common.h"

class ursNonCopyable
{
public:
	ursNonCopyable() = default;
	ursNonCopyable(const ursNonCopyable&) = delete;
	void operator=(const ursNonCopyable&) = delete;
};