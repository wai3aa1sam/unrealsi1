#pragma once

#include "ursFmt.h"
#include <Logging/LogMacros.h>

/*
~ reference:
- https://github.com/SimpleTalkCpp/SimpleTalkCpp_UnrealExamples/blob/main/Unreal_Cpp/MyProject/Source/MyProject/Common/MyLog.h
*/

struct UNREALSI1_API ursLogger 
{
	static void Output(int32 key, float timeToDisplay, const FString& msg);

	template<class... ARGS> static void _LogInternal(int32 key, float timeToDisplay, const char* format_str, ARGS&&... args);
};

template<class... ARGS> inline
void
ursLogger::_LogInternal(int32 key, float timeToDisplay, const char* format_str, ARGS&&... args) 
{
    FString tmp;
    fmt_format_to(ursFormat_FStringBackInserter(tmp), format_str, std::forward<ARGS>(args)...);
    Output(key, timeToDisplay, tmp);
}

// INDEX_NONE - new line with each call
#define URS_LOG(...)				do { ursLogger::_LogInternal(INDEX_NONE, 3,  __VA_ARGS__); } while(false)
#define URS_LOG_INLINE(KEY, ...)	do { ursLogger::_LogInternal(KEY, 3,  __VA_ARGS__); } while(false)


#define URS_ASSERT(X) check(X)