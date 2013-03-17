#include "Discordia.h"

#ifdef WIN32
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  reasonForCall, 
					  LPVOID lpReserved
					  )
{
	switch(reasonForCall)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}

	return TRUE;
}

#endif