#ifndef ISURFACE_CODEC_H_INCLUDED
#define ISURFACE_CODEC_H_INCLUDED

#include "ISurface.h"
#include "IFileReader.h"

namespace Discordia
{
	namespace Graphics
	{
		/** 
		 *	SurfaceCodec is an interface that image laoding classes inherit to specifically
		 *  load a imagetype. (See examples under the folder Codec).
		 */
		class ISurfaceCodec
		{
		public:
			virtual ~ISurfaceCodec() {}

			virtual bool		CanDecodeSurface(IO::IFileReader* fileReader) = 0;
			virtual ISurface*	Decode(IO::IFileReader* fileReader) = 0;

		protected:
			ISurfaceCodec() {}
		};
	}
}

#endif