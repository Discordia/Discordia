#ifndef ISURFACE_H_INCLUDED
#define ISURFACE_H_INCLUDED

#include "Dimension2D.h"
#include "Types.h"

namespace Discordia
{
	namespace Graphics
	{
		enum ColorFormat
		{
			COLOR_R8G8B8A8 = 0,
			COLOR_R5G5B5A1,
			COLOR_R8G8B8,
			COLOR_R5G6B5
		};

		/**
		 *  Interface for an image surface loaded or created on the fly.	
		 */
		class ISurface
		{
		public:
			virtual ~ISurface() {}

			virtual void*					Lock() = 0;
			virtual void					Unlock() = 0;
			virtual const Dimension2D<s32>& GetDimension() = 0;
			virtual ColorFormat				GetColorFormat() = 0;
			virtual const u16&				GetBits() = 0;
			virtual const u16&				GetBytes() = 0;

		protected:
			ISurface() {}
		};
	}
}



#endif