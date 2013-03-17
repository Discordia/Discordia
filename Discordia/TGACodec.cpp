#include <fstream>
#include "TGACodec.h"
#include "Surface.h"

namespace Discordia
{
	namespace Graphics
	{
		TGACodec::TGACodec()
			: ISurfaceCodec()
		{
		}

		TGACodec::~TGACodec()
		{
		}

		bool TGACodec::CanDecodeSurface(IO::IFileReader* fileReader)
		{
			c8 fotter[18];

			fileReader->Seek(-18, std::ios::end);
			
			if (!fileReader->Read(fotter, 18))
				return false;

			// A tga file should have the last 18 bytes as TRUEVISION-XFILE
			// and a terminator char (zero).
			if (string(fotter) == "TRUEVISION-XFILE.")
			{
				fileReader->Seek(0, std::ios::beg);
				return true;
			}

			return false;
		}

		// Loosley derived TGA loader from www.gametutorials.com
		ISurface* TGACodec::Decode(IO::IFileReader* fileReader)
		{
			ISurface* surface = 0;
			u8 length;
			u8 imageType;
			u16 width;
			u16 height;
			u8 bits;
			u16 bytes;
			u8* imageData;
			s32 stride;
	
			// Read length from header to pixel data
			fileReader->Seek(0, std::ios::beg);
			fileReader->Read((c8*)&length, sizeof(length));
			fileReader->Seek(1, std::ios::cur);

			// Read image type
			fileReader->Read((c8*)&imageType, 1);
			fileReader->Seek(9, std::ios::cur);

			// Read width, height, and bits
			fileReader->Read((c8*)&width, 2);
			fileReader->Read((c8*)&height, 2);
			fileReader->Read((c8*)&bits, 1);

			// Set file pointer to where the pixel data starts
			fileReader->Seek(length + 1, std::ios::cur);

			if (imageType != TGA_RLE)
			{
				if(bits == 24 || bits == 32)
				{
					bytes = bits / 8;
					stride = bytes*width;
					imageData = new u8[stride*height];

					// Load in all the pixel data line by line
					for(int i = 0; i < height; i++)
					{
						u8* line = &(imageData[stride*i]);
						fileReader->Read((c8*)line, stride);

						// Swap R and B, because TGA is stored as BGR and 
						// I wan't it as RGB
						for (int j=0; j < stride; j += bytes)
						{
							int temp = line[j];
							line[j] = line[j+2];
							line[j+2] = temp;
						}
					}
	
				}
				else if (bits == 16)
				{
					u16 pixel = 0;
					s32 r=0, g=0, b=0;

					bytes = 3;
					stride = bytes * width;
					imageData = new u8[stride * height];

					// Load in all the pixel data pixel by pixel
					for(int i = 0; i < width*height; i++)
					{
						fileReader->Read((c8*)&pixel, sizeof(u16));

						// Convert a 16-bit pixel into an R, G, B
						b = (pixel & 0x1f) << 3;
						g = ((pixel >> 5) & 0x1f) << 3;
						r = ((pixel >> 10) & 0x1f) << 3;

						// This essentially assigns the color to our array and swaps the
						// B and R values at the same time.
						imageData[i * 3 + 0] = r;
						imageData[i * 3 + 1] = g;
						imageData[i * 3 + 2] = b;
					}
				}

			}
			else
			{
				u8 rleID = 0;
				s32 colorsRead = 0;
				s32 i = 0;
				bytes = bits / 8;
				stride = bytes * width;

				imageData = new u8[stride * height];
				u8* colors = new u8[bytes];

				while(i < width*height)
				{
					fileReader->Read((c8*)&rleID, 1);

					// If rle code is less than 128 -> no encoding
					if(rleID < 128)
					{
						rleID++;

						while(rleID)
						{
							fileReader->Read((c8*)colors, 1*bytes);

							imageData[colorsRead + 0] = colors[2];
							imageData[colorsRead + 1] = colors[1];
							imageData[colorsRead + 2] = colors[0];

							if(bits == 32)
								imageData[colorsRead + 3] = colors[3];

							i++;
							rleID--;
							colorsRead += bytes;
						}
					}
					else // We got encoding
					{
						rleID -= 127;
						
						// Read color...and
						fileReader->Read((c8*)colors, 1*bytes);

						//..then read how many pixels have the same color
						while(rleID)
						{
							imageData[colorsRead + 0] = colors[2];
							imageData[colorsRead + 1] = colors[1];
							imageData[colorsRead + 2] = colors[0];

							if(bits == 32)
								imageData[colorsRead + 3] = colors[3];

							i++;
							rleID--;
							colorsRead += bytes;
						}

					}
				}

				delete[] colors;
			}

			// Create surfaces.
			if (bytes == 3)
				surface = new Surface(COLOR_R8G8B8, Dimension2D<s32>(width, height), imageData);
			else if (bytes == 4)
				surface = new Surface(COLOR_R8G8B8A8, Dimension2D<s32>(width, height), imageData);

			return surface;
		}	
	}
}