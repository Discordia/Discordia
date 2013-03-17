#include "RenderDeviceStub.h"

namespace Discordia
{
	namespace Graphics
	{
		RenderDeviceStub::RenderDeviceStub(const Dimension2D<s32>& windowDim)
			: IRenderDevice(), isActive(false), resourceManager(0), vertexBuffer(0), indexBuffer(0)
		{
			SDL_putenv("SDL_VIDEODRIVER=directx");
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
				Destroy();

			videoInfo = SDL_GetVideoInfo();

			if (!videoInfo)
				Destroy();

			Viewports* vp = new Viewports();
			renderEnv = new RenderEnviorment(windowDim, vp);
		}

		RenderDeviceStub::~RenderDeviceStub()
		{
			Destroy();
		}

		void RenderDeviceStub::Destroy()
		{
			// Destroy our surface (window)
			if (surface)
			{
				SDL_FreeSurface(surface);
				surface = 0;
			}

			// Destroy vertexBuffer and indexBuffer
			if (indexBuffer)
			{
				delete indexBuffer;
				indexBuffer = 0;
			}

			if (vertexBuffer)
			{
				delete vertexBuffer;
				vertexBuffer = 0;
			}

			// Exit SDL
			SDL_Quit();
		}

		bool RenderDeviceStub::IsActive()
		{
			return isActive;
		}

		bool RenderDeviceStub::RunEventLoop(SDL_Event event)
		{
			switch(event.type)
			{
			case SDL_ACTIVEEVENT:
				if (event.active.gain == 0)
					isActive = false;
				else
					isActive = true;
				break;	

			case SDL_VIDEORESIZE:
				surface = SDL_SetVideoMode(event.resize.w, event.resize.h, bits, videoFlags);

				if ( !surface )
					return false;

				Resize(Dimension2D<s32>(event.resize.w, event.resize.h));
				break;

			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					return false;
				}
				break;

			case SDL_QUIT:
				return false;

			default:
				break;
			}

			return true;
		}

		IBufferObject* RenderDeviceStub::GetVertexBuffer()
		{
			return vertexBuffer;
		}

		IBufferObject* RenderDeviceStub::GetIndexBuffer()
		{
			return indexBuffer;
		}

		RenderEnviorment* RenderDeviceStub::GetRenderEnviorment()
		{
			return renderEnv;
		}

		void RenderDeviceStub::SetRenderEnviorment(RenderEnviorment* re)
		{
			renderEnv = re;
		}

	}
}