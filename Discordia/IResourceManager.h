#ifndef IRESOURCE_MANAGER
#define IRESOURCE_MANAGER

#include <string>
#include <memory>
#include "ITexture.h"
#include "IGPUProgram.h"
#include "IShaderObject.h"
#include "IVirtualFileSystem.h"
#include "IPixelBuffer.h"
#include "Dimension2D.h"

using std::string;
using std::weak_ptr;
using std::shared_ptr;

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  Interface for the resource manager that creates/loads everything in the engine and returns
		 *  a "handel-interface".
		 */
		class IResourceManager
		{
		public:
			virtual ~IResourceManager() {}

			virtual weak_ptr<ITexture>			GetTexture(string filename) = 0;
			virtual shared_ptr<ITexture>		CreateNewTexture(const Dimension2D<s32>& textureDim) = 0;
			virtual weak_ptr<IGPUProgram>		GetGPUProgram(string programName) = 0;
			virtual weak_ptr<IShaderObject>		GetVertexShader(string filename) = 0;
			virtual weak_ptr<IShaderObject>		GetPixelShader(string filename) = 0;
			virtual shared_ptr<IPixelBuffer>	CreateNewPixelBuffer(const Dimension2D<s32>& pbufferDim) = 0;

			virtual IO::IVirtualFileSystem* GetFileSystem() = 0;

		protected:
			IResourceManager() {}
		};
	}
}

#endif