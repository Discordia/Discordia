#include "BMPCodec.h"

namespace Discordia
{
	namespace Graphics
	{
		BMPCodec::BMPCodec()
		{
		}

		BMPCodec::~BMPCodec()
		{
		}

		bool BMPCodec::CanDecodeSurface(IO::IFileReader* fileReader)
		{
			c8 header[54];

			fileReader->Seek(0, std::ios::beg);

			if (fileReader->Read(header, 54))
				return false;

			// A bmp file should have the 2 first bytes of the header set to B and M
			if (header[0] == 'B' && header[1] == 'M')
			{
				fileReader->Seek(0, std::ios::beg);
				return true;
			}

			return false;
		}

		ISurface* BMPCodec::Decode(IO::IFileReader* fileReader)
		{
			return 0;
		}
	}
}