#include "Surface.h"

namespace Discordia
{
	namespace Graphics
	{
		Surface::Surface(ColorFormat colorFormat, const Dimension2D<s32>& dim)
			: ISurface(), colorFormat(colorFormat), dimension(dim), surfaceData(0)
		{
			Init();
		}

		Surface::Surface(ColorFormat colorFormat, const Dimension2D<s32>& dim, void* surfaceData)
			: ISurface(), colorFormat(colorFormat), dimension(dim), surfaceData(surfaceData)
		{
			Init();
		}

		Surface::~Surface()
		{
			if (surfaceData)
			{
				delete surfaceData;
				surfaceData = 0;
			}
		}

		void Surface::Init()
		{
			switch(colorFormat)
			{
			case COLOR_R8G8B8A8:
				bits = 32;
				break;

			case COLOR_R5G5B5A1:
				bits = 16;
				break;

			case COLOR_R8G8B8:
				bits = 24;
				break;

			case COLOR_R5G6B5:
				bits = 16;
				break;
			}
	
			bytes = bits / 8;

			// Mayby should be removed do to speed
			if (!surfaceData)
				surfaceData =  new u8[dimension.width*dimension.height*bytes];
		}

		void* Surface::Lock()
		{
			isLocked = true;
			return surfaceData;
		}

		void  Surface::Unlock()
		{
			isLocked = false;
		}

		const Dimension2D<s32>& Surface::GetDimension()
		{
			return dimension;
		}

		ColorFormat Surface::GetColorFormat()
		{
			return colorFormat;
		}

		const u16& Surface::GetBits()
		{
			return bits;
		}

		const u16& Surface::GetBytes()
		{
			return bytes;
		}
	}
}