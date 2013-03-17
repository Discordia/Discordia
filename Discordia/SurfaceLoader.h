#ifndef SURFACE_LOADER_H_INCLUDED
#define SURFACE_LOADER_H_INCLUDED

#include <vector>
#include <memory>
#include "ISurfaceCodec.h"

using std::vector;
using std::shared_ptr;

namespace Discordia
{
	namespace Graphics
	{
		/** 
		 *	Class that holds a list of all surface codecs, that is all the image types the 
		 *  engine can load. All image laoding goes through here.
		 */
		class SurfaceLoader
		{
		public:
			SurfaceLoader();
			~SurfaceLoader();

			ISurface*	LoadSurface(IO::IFileReader* fileReader);

			void		RegisterCodec(ISurfaceCodec* codec);
			void		UnregisterCodec(ISurfaceCodec* codec);

		private:
			vector<shared_ptr<ISurfaceCodec> > codecList;
		};
	}
}

#endif