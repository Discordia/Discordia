#include "ResourceManager.h"
#include "FileSystem.h"
#include "TGACodec.h"

namespace Discordia
{
	namespace Graphics
	{
		ResourceManager::ResourceManager()
			: IResourceManager(), surfaceLoader(0)
		{
			// Create filesystem
			fileSystem = new IO::FileSystem();

			// Create surfaceLoaders
			surfaceLoader = new SurfaceLoader();

			// Add known codecs
			ISurfaceCodec* tgaCodec = new TGACodec();
			surfaceLoader->RegisterCodec(tgaCodec);
		}

		ResourceManager::~ResourceManager()
		{
			if (surfaceLoader)
			{
				delete surfaceLoader;
				surfaceLoader = 0;
			}
		}

		IO::IVirtualFileSystem* ResourceManager::GetFileSystem()
		{
			return fileSystem;
		}

		shared_ptr<ITexture> ResourceManager::GetStoredTexture(string fileName)
		{
			map<string, shared_ptr<ITexture> >::iterator texIt;
			texIt = textures.begin();

			while (texIt != textures.end() && texIt->first != fileName)
				texIt++;

			if (texIt == textures.end())
			{
				ITexture* tex = 0;			
				return shared_ptr<ITexture>(tex);
			}

			return texIt->second;
		}

		shared_ptr<IShaderObject> ResourceManager::GetStoredShader(string fileName)
		{
			map<string, shared_ptr<IShaderObject> >::iterator shIt;
			shIt = shaders.begin();

			while (shIt != shaders.end() && shIt->first != fileName)
				shIt++;

			if (shIt == shaders.end())
			{
				IShaderObject* shader = 0;
				return shared_ptr<IShaderObject>(shader);
			}

			return shIt->second;
		}

		shared_ptr<IGPUProgram> ResourceManager::GetStoredProgram(string programName)
		{
			map<string, shared_ptr<IGPUProgram> >::iterator progIt;
			progIt = programs.begin();

			while (progIt != programs.end() && progIt->first != programName)
				progIt++;

			if (progIt == programs.end())
			{
				IGPUProgram* program = 0;
				return shared_ptr<IGPUProgram>(program);
			}

			return progIt->second;
		}
	}
}