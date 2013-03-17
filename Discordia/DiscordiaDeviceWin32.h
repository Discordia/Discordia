#ifndef DISCORDIA_DEVICE_WIN32_H_INCLUDED
#define DISCORDIA_DEVICE_WIN32_H_INCLUDED

#ifdef WIN32

#include <windows.h>
#include <string>
#include "DiscordiaDeviceStub.h"

using std::string;
using namespace Discordia::Graphics;

namespace Discordia
{
	class DiscordiaDeviceWin32 : public DiscordiaDeviceStub
	{
	public:
		DiscordiaDeviceWin32();
		virtual ~DiscordiaDeviceWin32();

		IRenderDevice* CreateRenderDevice(DeviceType deviceType, 
			const Dimension2D<s32>& windowDim, u16 bits, bool fullscreen);

	protected:
		void CreateSubSystems();
	};
}

#endif
#endif