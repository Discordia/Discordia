#ifndef WIN32_OGL_PIXEL_BUFFER_H_INCLUDED
#define WIN32_OGL_PIXEL_BUFFER_H_INCLUDED

#include "IPixelBuffer.h"
#include "Dimension2D.h"
#include "Types.h"
	
#ifdef WIN32
#include <Windows.h>
#include <gl/GLee.h>

namespace Discordia
{
	namespace Graphics
	{
		/** 
		 *	Windows only OpenGL pixel buffer, used for render to texture. Implemented
		 *  with the GL_EXT_pbuffer extension.
		 */
		class Win32OGLPixelBuffer : public IPixelBuffer
		{
		public:
			Win32OGLPixelBuffer(const Dimension2D<s32>& bufferDim);
			virtual ~Win32OGLPixelBuffer();

			bool Create();
			bool SetBufferAsRenderTarget();
			bool SetWindowAsRenderTarget();
			bool BindBufferToTexture();
			bool ReleaseBufferFromTexture();
			void ShareData();

		protected:
			void Destroy();

			HDC					winDC;
			HWND				hWin;
			HGLRC				winOGLRC;
			HDC					pbufferDC;
			HGLRC				pbufferOGLRC;
			HPBUFFERARB			pixelBuffer;
			Dimension2D<s32>	bufferDim;
		};
	}
}

#endif // Win32	
#endif