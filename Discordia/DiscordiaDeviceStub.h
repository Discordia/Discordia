#ifndef DISCORDIA_DEVICE_STUB_H_INCLUDED
#define DISCORDIA_DEVICE_STUB_H_INCLUDED

#include "SDL.h"
#include "IDiscordiaDevice.h"
#include "IEventListener.h"
#include "Logger.h"

namespace Discordia
{
	class DiscordiaDeviceStub : public IDiscordiaDevice
	{
	public:
		virtual ~DiscordiaDeviceStub();

		virtual bool Run();
		virtual Graphics::IRenderDevice*	GetRenderDevice();
		virtual Scene::ISceneManager*		GetSceneManager();


	protected:
		DiscordiaDeviceStub();

		void PostEvent(const Event& event);

	protected:

		// Subsystems
		Graphics::IRenderDevice*	renderDevice;
		Shader::IShaderSystem*		shaderSystem;
		Scene::ISceneManager*		sceneManager;
		Logger*						logger;

		// Variables
		SDL_Event					event;
	};
}

#endif