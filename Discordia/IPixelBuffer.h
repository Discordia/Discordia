#ifndef IPIXEL_BUFFER_H_INCLUDED
#define IPIXEL_BUFFER_H_INCLUDED

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  Interface that represents a pixel buffer used for offscreen drawing, i.e.
		 *  render to texture.
		 */
		class IPixelBuffer
		{
		public:
			virtual ~IPixelBuffer() {}
			
			virtual bool Create() = 0;
			virtual bool SetBufferAsRenderTarget() = 0;
			virtual bool SetWindowAsRenderTarget() = 0;
			virtual bool BindBufferToTexture() = 0;
			virtual bool ReleaseBufferFromTexture() = 0;

		protected:
			IPixelBuffer() {}
		};
	}
}

#endif