#ifndef BMP_CODEC_H_INCLUDED
#define BMP_CODEC_H_INCLUDED

#include "ISurfaceCodec.h"

namespace Discordia
{
	namespace Graphics
	{
		class BMPCodec : public ISurfaceCodec
		{
		public:
			BMPCodec();
			virtual ~BMPCodec();

			bool		CanDecodeSurface(IO::IFileReader* fileReader);
			ISurface*	Decode(IO::IFileReader* fileReader);
		};
	}
}

#endif