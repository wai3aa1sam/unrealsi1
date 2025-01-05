#pragma once

#include "../detect_platform/urs_detect_platform.h"

#define URS_FILE __FILE__
#define URS_LINE __LINE__
#define URS_FUNC URS_FUNC_NAME_SZ

#define URS_COMMA ,
#define URS_EMPTY
#define URS_ARGS(...) __VA_ARGS__
#define URS_STRINGIFY_IMPL(...)	#__VA_ARGS__
#define URS_STRINGIFY(...)		URS_STRINGIFY_IMPL(__VA_ARGS__)

#define URS_IDENTITY(X) X
#define URS_CALL(M, ARGS) URS_IDENTITY( M(ARGS) )

#define URS_CONCAT_IMPL(A, B)		A ## B
#define URS_CONCAT(A, B)			URS_CONCAT_IMPL(A, B)
#define URS_CONCAT_TO_STR(A, B)		URS_STRINGIFY(A) URS_STRINGIFY(B)

#define URS_VA_ARGS_COUNT(...) URS_IDENTITY( URS_VA_ARGS_COUNT_INTERNAL(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1) )
#define URS_VA_ARGS_COUNT_INTERNAL(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, COUNT, ...) COUNT

#define URS_VAR_NAME(NAME)			URS_CONCAT(URS_CONCAT(_temp_, NAME), URS_LINE)

#define URS_UNUSED(var) (void)var

#define URS_ASSERT(X, ...) check(X)
