#include "DiscordiaDeviceLinux.h"

#ifdef LINUX
#include "Discordia.h"

namespace Discordia
{
	DiscordiaDeviceLinux::DiscordiaDeviceLinux()
	{

	}

	DiscordiaDeviceLinux::~DiscordiaDeviceLinux()
	{
		if (renderDevice)
		{
			delete renderDevice;
			renderDevice = 0;
		}

	}

	void DiscordiaDeviceLinux::LoadLibrary(string name, LibraryType libType)
	{

	}

	IDiscordiaDevice* CreateDevice()
	{
		return new DiscordiaDeviceLinux();
	}
}

#endif