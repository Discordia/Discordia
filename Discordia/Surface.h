#ifndef SURFACE_H_INCLUDED
#define SURFACE_H_INCLUDED

#include "ISurface.h"

namespace Discordia
{
	namespace Graphics
	{
		class Surface : public ISurface
		{
		public:
			Surface(ColorFormat colorFormat, const Dimension2D<s32>& dim, void* surfaceData);
			Surface(ColorFormat colorFormat, const Dimension2D<s32>& dim);
			virtual ~Surface();

			virtual void*					Lock();
			virtual void					Unlock();
			virtual const Dimension2D<s32>& GetDimension();
			virtual ColorFormat				GetColorFormat();
			virtual const u16&				GetBits();
			virtual const u16&				GetBytes();

		protected:
			void Init();

		protected:
			void* surfaceData;
			bool isLocked;
			Dimension2D<s32> dimension;
			ColorFormat colorFormat;
			u16 bits;
			u16 bytes;
		};
	}
}


#endif