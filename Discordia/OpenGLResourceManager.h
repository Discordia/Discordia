#ifndef OPENGL_RESOURCE_MANAGER_H_INCLUDED
#define OPENGL_RESOURCE_MANAGER_H_INCLUDED

#include "ResourceManager.h"
#include "Logger.h"

namespace Discordia
{
	namespace Graphics
	{
		/** 
		 *	OpenGL resourceManager, from here you can load textures, vertex shaders, pixel shaders and 
		 *  create new pixel buffers, GLSL programs, and empty textures.
		 *  TODO: Should create vertex buffer, and index buffer here too and not in the render device.
		 *  TODO: Should create VRAM cache, and RAM cahce, and keep better control on loaded resources.
		 */
		class OpenGLResourceManager : public ResourceManager
		{
		public:
			OpenGLResourceManager(Logger* logger);
			virtual ~OpenGLResourceManager();

			weak_ptr<ITexture>			GetTexture(string fileName);
			shared_ptr<ITexture>		CreateNewTexture(const Dimension2D<s32>& textureDim);
			weak_ptr<IGPUProgram>		GetGPUProgram(string fileName);
			weak_ptr<IShaderObject>		GetVertexShader(string fileName);
			weak_ptr<IShaderObject>		GetPixelShader(string programName);
			shared_ptr<IPixelBuffer>	CreateNewPixelBuffer(const Dimension2D<s32>& pbufferDim);

		protected:
			weak_ptr<ITexture>		CreateTextureFromFile(IO::IFileReader* fileReader);
			Logger*					logger;
		};
	}
}

#endif