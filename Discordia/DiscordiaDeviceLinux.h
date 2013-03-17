#ifndef DISCORDIA_DEVICE_LINUX_H_INCLUDED
#define DISCORDIA_DEVICE_LINUX_H_INCLUDED

#ifdef LINUX

#include "DiscordiaDeviceStub.h"

namespace Discordia
{
	class DiscordiaDeviceLinux : public DiscordiaDeviceStub
	{
	public:
		DiscordiaDeviceLinux();
		virtual ~DiscordiaDeviceLinux();

	protected:
		void LoadLibrary(string name, LibraryType libType = RENDER_LIB);

	private:

	};
}

#endif
#endif