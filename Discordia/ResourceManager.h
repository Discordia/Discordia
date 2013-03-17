#ifndef RESOURCE_MANAGER_H_INCLUDED
#define RESOURCE_MANAGER_H_INCLUDED

#include <map>
#include <algorithm>
#include <utility>
#include "IResourceManager.h"
#include "SurfaceLoader.h"
#include "ITexture.h"

using std::map;
using std::pair;

namespace Discordia
{
	namespace Graphics
	{
		class ResourceManager : public IResourceManager
		{
		public:
			virtual ~ResourceManager();

			IO::IVirtualFileSystem*		GetFileSystem();

		protected:
			ResourceManager();
	
			virtual weak_ptr<ITexture>		CreateTextureFromFile(IO::IFileReader* fileReader) = 0;

			shared_ptr<ITexture>			GetStoredTexture(string fileName);
			shared_ptr<IShaderObject>		GetStoredShader(string fileName);
			shared_ptr<IGPUProgram>			GetStoredProgram(string programName);
	
		protected:
			SurfaceLoader* surfaceLoader;
			IO::IVirtualFileSystem* fileSystem;
			map<string, shared_ptr<ITexture> > textures;
			map<string, shared_ptr<IShaderObject> > shaders;
			map<string, shared_ptr<IGPUProgram> > programs;
		};
	}
}

#endif