#ifndef TGA_CODEC_H_INCLUDED
#define TGA_CODEC_H_INCLUDED

#include "SurfaceLoader.h"

namespace Discordia
{
	namespace Graphics
	{
		enum TGAFormat
		{
			TGA_RGB = 1,
			TGA_A	= 2,
			TGA_RLE	= 3
		};

		class TGACodec : public ISurfaceCodec
		{
		public:
			TGACodec();
			virtual ~TGACodec();

			bool		CanDecodeSurface(IO::IFileReader* fileReader);
			ISurface*	Decode(IO::IFileReader* fileReader);			
		};
	}
}

#endif