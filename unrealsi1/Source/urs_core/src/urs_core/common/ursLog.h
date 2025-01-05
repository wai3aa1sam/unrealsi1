#pragma once

#include "../marco/urs_core_marco.h"
#include "ursFmt.h"
#include <Logging/LogMacros.h>

/*
~ reference:
- https://github.com/SimpleTalkCpp/SimpleTalkCpp_UnrealExamples/blob/main/Unreal_Cpp/MyProject/Source/MyProject/Common/MyLog.h
*/

struct UNREALSI1_API ursLogger 
{
	static void output(int32 key, float timeToDisplay, const FString& msg);

	template<class... ARGS> static void _logInternal(int32 key, float timeToDisplay, const char* format_str, ARGS&&... args);
};

template<class... ARGS> inline
void
ursLogger::_logInternal(int32 key, float timeToDisplay, const char* format_str, ARGS&&... args) 
{
    FString tmp;
    fmt_format_to(ursFormat_FStringBackInserter(tmp), format_str, std::forward<ARGS>(args)...);
    output(key, timeToDisplay, tmp);
}

// INDEX_NONE - new line with each call
#define URS_LOG(...)				    do { ursLogger::_logInternal(INDEX_NONE, 3,  __VA_ARGS__); }    while(false)
#define URS_LOG_INLINE(...)	            do { ursLogger::_logInternal(__LINE__, 3,  __VA_ARGS__); }      while(false)
#define URS_LOG_INLINE_KEY(KEY, ...)	do { ursLogger::_logInternal(KEY, 3,  __VA_ARGS__); }           while(false)

/*
* URS_DUMP_VAR
*/
#define URS_DUMP_VAR_1(v0)								do{ URS_LOG("DUMP_VAR: {}=[{}]",										#v0, (v0)); } while(false)
#define URS_DUMP_VAR_2(v0, v1)							do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}]",								#v0, (v0), #v1, (v1)); } while(false)
#define URS_DUMP_VAR_3(v0, v1, v2)						do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}]",						#v0, (v0), #v1, (v1), #v2, (v2)); } while(false)
#define URS_DUMP_VAR_4(v0, v1, v2, v3)					do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}]",				#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3)); } while(false)
#define URS_DUMP_VAR_5(v0, v1, v2, v3, v4)				do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",	#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4)); } while(false)

#define URS_DUMP_VAR_6(v0, v1, v2, v3, v4, v5)			do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",						\
														#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5)); } while(false)
#define URS_DUMP_VAR_7(v0, v1, v2, v3, v4, v5, v6)		do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",				\
														#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5), #v6, (v6)); } while(false)
#define URS_DUMP_VAR_8(v0, v1, v2, v3, v4, v5, v6, v7)	do{ URS_LOG("DUMP_VAR: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",		\
														#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5), #v6, (v6), #v7, (v7)); } while(false)

#define URS_DUMP_VAR_SELECT(COUNT) URS_DUMP_VAR_##COUNT
#define URS_DUMP_VAR(...) URS_IDENTITY(URS_CALL(URS_DUMP_VAR_SELECT, URS_VA_ARGS_COUNT(__VA_ARGS__) (__VA_ARGS__)))

/*
* URS_DUMP_VAR_INLINE
*/
#define URS_DUMP_VAR_INLINE_1(v0)								do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}]",											#v0, (v0)); } while(false)
#define URS_DUMP_VAR_INLINE_2(v0, v1)							do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}]",									#v0, (v0), #v1, (v1)); } while(false)
#define URS_DUMP_VAR_INLINE_3(v0, v1, v2)						do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}], {}=[{}]",						#v0, (v0), #v1, (v1), #v2, (v2)); } while(false)
#define URS_DUMP_VAR_INLINE_4(v0, v1, v2, v3)					do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}], {}=[{}], {}=[{}]",				#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3)); } while(false)
#define URS_DUMP_VAR_INLINE_5(v0, v1, v2, v3, v4)				do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",		#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4)); } while(false)

#define URS_DUMP_VAR_INLINE_6(v0, v1, v2, v3, v4, v5)			do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",						\
																#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5)); } while(false)
#define URS_DUMP_VAR_INLINE_7(v0, v1, v2, v3, v4, v5, v6)		do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",				\
																#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5), #v6, (v6)); } while(false)
#define URS_DUMP_VAR_INLINE_8(v0, v1, v2, v3, v4, v5, v6, v7)	do{ URS_LOG_INLINE("DUMP_VAR_INLINE: {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}], {}=[{}]",		\
																#v0, (v0), #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5), #v6, (v6), #v7, (v7)); } while(false)

#define URS_DUMP_VAR_INLINE_SELECT(COUNT) URS_DUMP_VAR_INLINE_##COUNT
#define URS_DUMP_VAR_INLINE(...) URS_IDENTITY(URS_CALL(URS_DUMP_VAR_INLINE_SELECT, URS_VA_ARGS_COUNT(__VA_ARGS__) (__VA_ARGS__)))

