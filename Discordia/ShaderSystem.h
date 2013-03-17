#ifndef SHADER_SYSTEM_H_INCLUDED
#define SHADER_SYSTEM_H_INCLUDED

#include "IShaderSystem.h"
#include "IRenderDevice.h"
#include "IResourceManager.h"
#include "GeometryChunk.h"
#include "IBufferObject.h"
#include "IPixelBuffer.h"
#include "IGPUProgram.h"
#include "IShaderObject.h"

using Discordia::Graphics::IPixelBuffer;
using Discordia::Graphics::IGPUProgram;
using Discordia::Graphics::IShaderObject;

namespace Discordia
{
	namespace Shader
	{
		class ShaderSystem : public IShaderSystem
		{
		public:
			ShaderSystem(Graphics::IRenderDevice* renderDevice, Graphics::IResourceManager* resourceManager);
			virtual ~ShaderSystem();

			RenderQueue*	GetRenderQueue();
			void			SetRenderCamera(Scene::ICamera* camera);
			void			DrawRenderQueue();

		protected:
			void RenderChunk(GeometryChunk* chunk);

			Graphics::IRenderDevice*	renderDevice;
			Graphics::IResourceManager* resourceManager;
			RenderQueue*				renderQueue;
			Scene::ICamera*				renderCamera;
			Graphics::IBufferObject*	vertexBuffer;
			Graphics::IBufferObject*	indexBuffer;
			shared_ptr<IPixelBuffer>	pbuffer;
			shared_ptr<ITexture>		dynamicTexture;
			shared_ptr<IGPUProgram>		program;
			u32							globalVOffset;
			u32							globalIOffset;
		};
	}
}

#endif