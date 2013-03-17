#ifndef DISCORDIA_H_INCLUDED
#define DISCORDIA_H_INCLUDED

#include "IDiscordiaDevice.h"
#include "Color.h"
#include "Vertex.h"

#ifdef WIN32
#ifdef DISCORDIA_EXPORTS
#define DISCORDIA_API __declspec(dllexport)
#else
#define DISCORDIA_API __declspec(dllimport)
#endif // DISCORDIA_EXPORTS
#else
#define DISCORDIA_API
#endif // WIN32

namespace Discordia
{
	DISCORDIA_API IDiscordiaDevice* CreateDevice();
}

#endif