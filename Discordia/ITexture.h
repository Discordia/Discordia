#ifndef ITEXTURE_H_INCLUDED
#define ITEXTURE_H_INCLUDED

#include "Types.h"

namespace Discordia
{
	namespace Graphics
	{
		enum TextureQuality
		{
			TQ_HIGH_QUALITY = 0,
			TQ_AVRAGE_QUALITY,
			TQ_LOW_QUALITY,
			TQ_WORST_QUALITY
		};

		/**
		 *  Interface for a texture.	
		 */
		class ITexture
		{
		public:
			virtual ~ITexture() {}

			virtual u32		GetTextureID() = 0;
			virtual bool	IsCreated() = 0;

		protected:
			ITexture() {}
		};
	}

}


#endif