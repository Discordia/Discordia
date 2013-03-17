#ifndef JPG_CODEC_H_INCLUDED
#define JPG_CODEC_H_INCLUDED

#include <stdio.h>
#include "ISurfaceCodec.h"
extern "C" {
#include "jpeglib/jconfig.h"
#include "jpeglib/jpeglib.h"
}

namespace Discordia
{
	namespace Graphics
	{
		class JPGCodec : public ISurfaceCodec
		{
		public:
			JPGCodec();
			virtual ~JPGCodec();
			
			bool		CanDecodeSurface(IO::IFileReader* fileReader);
			ISurface*	Decode(IO::IFileReader* fileReader);	

		private:
			static void SkipInputData(j_decompress_ptr cinfo, long count);
			static u8 FillInputBuffer(j_decompress_ptr cinfo);
			static void InitSource(j_decompress_ptr cinfo);
			static void TermSource(j_decompress_ptr cinfo);


		};
	}
}


#endif