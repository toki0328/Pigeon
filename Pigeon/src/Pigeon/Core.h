#pragma once

#ifdef PG_PLATFORM_WINDOWS
	#ifdef PG_BUILD_DLL
		#define PIGEON_API __declspec(dllexport)
	#else
		#define PIGEON_API __declspec(dllimport)
	#endif
#else
	#error Pigeon only support Windows!
#endif
