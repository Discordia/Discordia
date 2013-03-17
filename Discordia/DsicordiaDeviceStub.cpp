#include "DiscordiaDeviceStub.h"


namespace Discordia
{
	DiscordiaDeviceStub::DiscordiaDeviceStub()
		: IDiscordiaDevice(), renderDevice(0), shaderSystem(0), sceneManager(0)
	{
	}

	DiscordiaDeviceStub::~DiscordiaDeviceStub()
	{
		if (sceneManager)
		{
			delete sceneManager;
			sceneManager = 0;
		}
	}

	Graphics::IRenderDevice* DiscordiaDeviceStub::GetRenderDevice()
	{
		return renderDevice;
	}

	//Shader::IShaderSystem* DiscordiaDeviceStub::GetShaderSystem()
	//{
	//	return shaderSystem;
	//}

	Scene::ISceneManager* DiscordiaDeviceStub::GetSceneManager()
	{
		return sceneManager;
	}

	bool DiscordiaDeviceStub::Run()
	{
		if (!renderDevice || !sceneManager)
			return false;

		bool quit = false;

		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				Event newEvent;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					quit = true;
					break;

				default:
					newEvent.eventType = ET_KEY_EVENT;
					newEvent.KeyEvent.isDown = true;
					newEvent.KeyEvent.keyCode = (Discordia::KeyCode) event.key.keysym.sym;
					newEvent.KeyEvent.keyMode = (Discordia::KeyMode) event.key.keysym.mod;
					this->PostEvent(newEvent);
					break;
				}
				break;

			case SDL_KEYUP:
				newEvent.eventType = ET_KEY_EVENT;
				newEvent.KeyEvent.isDown = false;
				newEvent.KeyEvent.keyCode = (Discordia::KeyCode) event.key.keysym.sym;
				newEvent.KeyEvent.keyMode = (Discordia::KeyMode) event.key.keysym.mod;
				this->PostEvent(newEvent);
				break;

			case SDL_MOUSEMOTION:
				newEvent.eventType = ET_MOUSE_EVENT;
				newEvent.MouseEvent.event = MIE_MOUSE_MOVED;
				newEvent.MouseEvent.relX = event.motion.xrel;
				newEvent.MouseEvent.relY = event.motion.yrel;
				newEvent.MouseEvent.x = event.motion.x;
				newEvent.MouseEvent.y = event.motion.y;
				this->PostEvent(newEvent);
				break;

			case SDL_MOUSEBUTTONDOWN:
				newEvent.eventType = ET_MOUSE_EVENT;

				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					newEvent.MouseEvent.event = MIE_LEFT_MOUSE_BUTTON_DOWN;
					break;

				case SDL_BUTTON_MIDDLE:
					newEvent.MouseEvent.event = MIE_MIDDLE_MOUSE_BUTTON_DOWN;
					break;

				case SDL_BUTTON_RIGHT:
					newEvent.MouseEvent.event = MIE_RIGHT_MOUSE_BUTTON_DOWN;
					break;
				}
				
				this->PostEvent(newEvent);
				break;

			case SDL_MOUSEBUTTONUP:
				newEvent.eventType = ET_MOUSE_EVENT;

				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
					newEvent.MouseEvent.event = MIE_LEFT_MOUSE_BUTTON_UP;
					break;

				case SDL_BUTTON_MIDDLE:
					newEvent.MouseEvent.event = MIE_MIDDLE_MOUSE_BUTTON_UP;
					break;

				case SDL_BUTTON_RIGHT:
					newEvent.MouseEvent.event = MIE_RIGHT_MOUSE_BUTTON_UP;
					break;
				}

				this->PostEvent(newEvent);
				break;

			default:
				if (!renderDevice->RunEventLoop(event))
					quit = true;

				break;
			}
		}

		return quit;
	}

	void DiscordiaDeviceStub::PostEvent(const Event& event)
	{
		sceneManager->OnEvent(event);
	}

}