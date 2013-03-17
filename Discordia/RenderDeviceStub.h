#ifndef RENDER_DEVICE_STUB_H_INCLUDED
#define RENDER_DEVICE_STUB_H_INCLUDED

#include "IRenderDevice.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  Class inbetween IRednerDevice and a Opengl/DirectX/Software device. Should hold
		 *  all things for a NULL device, and should be queryable for system specs. 
		 *  TODO: See to it that the stub lives up to it's mening, it doesen't today.
		 */
		class RenderDeviceStub : public IRenderDevice
		{
		public:
			virtual ~RenderDeviceStub();

			virtual bool			RunEventLoop(SDL_Event event);
			virtual bool			IsActive();

			IBufferObject*			GetVertexBuffer();
			IBufferObject*			GetIndexBuffer();
			RenderEnviorment*		GetRenderEnviorment();
			void					SetRenderEnviorment(RenderEnviorment* re);

		protected:
			RenderDeviceStub(const Dimension2D<s32>& screenDim);

			void Destroy();

		protected:

			IBufferObject*				vertexBuffer;
			IBufferObject*				indexBuffer;
			IResourceManager*			resourceManager;
			RenderEnviorment*			renderEnv;

			Matrix4						matricies[MATRIX_COUNT];

			// SDL variables
			SDL_Surface*				surface;
			const SDL_VideoInfo*		videoInfo;
			u16							bits;
			s32							videoFlags;
			bool						fullscreen;
			bool						isActive;
			Dimension2D<s32>			windowDim;
		};
	}
}

#endif