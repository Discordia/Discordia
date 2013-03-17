#include "SurfaceLoader.h"
#include <algorithm>
#include <iterator>

using std::find;
using std::iterator;

namespace Discordia
{
	namespace Graphics
	{
		SurfaceLoader::SurfaceLoader()
		{
		}

		SurfaceLoader::~SurfaceLoader()
		{
		}

		ISurface* SurfaceLoader::LoadSurface(IO::IFileReader* fileReader)
		{
			ISurface* surface = 0;
			vector<shared_ptr<ISurfaceCodec> >::iterator codecIt;
			codecIt = codecList.begin();

			while (codecIt != codecList.end())
			{
				if ((*codecIt)->CanDecodeSurface(fileReader))
				{
					surface = (*codecIt)->Decode(fileReader);
					break;
				}

				codecIt++;
			}

			return surface;
		}

		void SurfaceLoader::RegisterCodec(ISurfaceCodec* codec)
		{
			codecList.push_back(shared_ptr<ISurfaceCodec>(codec));
		}

		void SurfaceLoader::UnregisterCodec(ISurfaceCodec* codec)
		{
			vector<shared_ptr<ISurfaceCodec> >::iterator codecIt; 
			codecIt = find(codecList.begin(), codecList.end(), shared_ptr<ISurfaceCodec>(codec));
			codecList.erase(codecIt);
		}
	}
}