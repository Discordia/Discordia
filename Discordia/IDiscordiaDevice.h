#ifndef IDISCORDIA_DEVICE_H_INCLUDED
#define IDISCORDIA_DEVICE_H_INCLUDED

#include "Types.h"
#include "Dimension2D.h"
#include "IRenderDevice.h"
#include "ISceneManager.h"
#include "IResourceManager.h"
#include "IShaderSystem.h"

namespace Discordia
{
	/**
	 *  The Discordia Device, the main interface in the engine. Exposes the engine API outwards.	
	 */
	class IDiscordiaDevice
	{
	public:
		virtual ~IDiscordiaDevice() {}

		virtual bool Run() = 0;
		virtual Graphics::IRenderDevice* CreateRenderDevice(Graphics::DeviceType deviceType, 
			const Dimension2D<s32>& windowDim, u16 bits, bool fullscreen) = 0;

		virtual Graphics::IRenderDevice*	GetRenderDevice() = 0;
		virtual Scene::ISceneManager*		GetSceneManager() = 0;

	protected:
		IDiscordiaDevice() {}
	};
}

#endif