#include "DiscordiaDeviceWin32.h"
#include "OpenGLRenderDevice.h"
#include "SceneManager.h"
#include "Shadersystem.h"

#ifdef WIN32

#include "Discordia.h"

namespace Discordia
{
	DiscordiaDeviceWin32::DiscordiaDeviceWin32()
		: DiscordiaDeviceStub()
	{
	}

	DiscordiaDeviceWin32::~DiscordiaDeviceWin32()
	{
		if (renderDevice)
		{
			delete renderDevice;
			renderDevice = 0;
		}
	}

	IRenderDevice* DiscordiaDeviceWin32::CreateRenderDevice(DeviceType deviceType, 
		const Dimension2D<s32>& windowDim, u16 bits, bool fullscreen)
	{
		if (renderDevice)
		{
			delete renderDevice;
			renderDevice = 0;
		}

		switch (deviceType)
		{
		case OPENGL_DEVICE:
			renderDevice = new OpenGLRenderDevice(windowDim, bits, fullscreen, logger);
			break;

		case DIRECTX9_DEVICE:
			
			break;

		case SOFTWARE_DEVICE:
			break;

		case NULL_DEVICE:
			break;
		}

		// Create sub systems
		CreateSubSystems();

		return renderDevice;
	}

	void DiscordiaDeviceWin32::CreateSubSystems()
	{
		if (shaderSystem)
		{
			delete shaderSystem;
			shaderSystem = 0;
		}

		if (sceneManager)
		{
			delete sceneManager;
			sceneManager = 0;
		}

		shaderSystem = new Shader::ShaderSystem(renderDevice, renderDevice->GetResourceManager());
		sceneManager = new Scene::SceneManager(shaderSystem, renderDevice->GetResourceManager(), renderDevice->GetRenderEnviorment());
	}

	DISCORDIA_API IDiscordiaDevice* CreateDevice()
	{
		return new DiscordiaDeviceWin32();
	}
}

#endif // WIN32