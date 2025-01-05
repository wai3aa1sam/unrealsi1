#pragma once

#define URS_DISABLE_ALL_WARNINGS() \
	__pragma(warning(push, 0)) \
	__pragma(warning(disable: 4172 4275 4702 4459 4530)) \
// ---

#define URS_RESTORE_ALL_WARNINGS() \
	__pragma(warning(pop)) \
// ---

#define	URS_FUNC_NAME_SZ			__FUNCTION__
#define URS_FUNC_FULLNAME_SZ		__FUNCSIG__
