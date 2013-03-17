#include "Win32OGLPixelBuffer.h"
#include "SDL_syswm.h"

#ifdef WIN32

namespace Discordia
{
	namespace Graphics
	{
		Win32OGLPixelBuffer::Win32OGLPixelBuffer(const Dimension2D<s32>& bufferDim)
			: IPixelBuffer(), pixelBuffer(0), bufferDim(bufferDim)
		{
			// Get window HWND under windows
			SDL_SysWMinfo wmInfo;
			SDL_VERSION(&wmInfo.version);
			SDL_GetWMInfo(&wmInfo);
			winOGLRC = wmInfo.hglrc;
			hWin = wmInfo.window;
			winDC = GetDC(hWin);
		}

		Win32OGLPixelBuffer::~Win32OGLPixelBuffer()
		{
			Destroy();
		}

		void Win32OGLPixelBuffer::Destroy()
		{
			if (winDC != NULL)
			{
				ReleaseDC(hWin, winDC);
				winDC = NULL;
			}

			if (pbufferOGLRC != NULL )
			{
				wglMakeCurrent( pbufferDC, pbufferOGLRC);
				wglDeleteContext(pbufferOGLRC);
				wglReleasePbufferDCARB(pixelBuffer, pbufferDC);
				wglDestroyPbufferARB(pixelBuffer);
				pbufferOGLRC = NULL;
			}

			if (pbufferDC != NULL )
			{
				ReleaseDC(hWin, pbufferDC);
				pbufferDC = NULL;
			}
		}

		bool Win32OGLPixelBuffer::Create()
		{
			// TODO: Check that extensions exist
			// TODO: 32 bit depth buffer???
			// Add paramers to sopport doublebuffering etc...
			s32 pfAttr[] =
			{
				WGL_SUPPORT_OPENGL_ARB, TRUE,       // P-buffer will be used with OpenGL
				WGL_DRAW_TO_PBUFFER_ARB, TRUE,      // Enable render to p-buffer
				WGL_BIND_TO_TEXTURE_RGBA_ARB, TRUE, // P-buffer will be used as a texture
				WGL_RED_BITS_ARB, 8,                // At least 8 bits for RED channel
				WGL_GREEN_BITS_ARB, 8,              // At least 8 bits for GREEN channel
				WGL_BLUE_BITS_ARB, 8,               // At least 8 bits for BLUE channel
				WGL_ALPHA_BITS_ARB, 8,              // At least 8 bits for ALPHA channel
				WGL_DEPTH_BITS_ARB, 16,             // At least 16 bits for depth buffer 
				WGL_DOUBLE_BUFFER_ARB, FALSE,       // We don't require double buffering
				0                                   // Zero terminates the list
			}; 

			u32 count = 0;
			s32 pixelFormat;
			wglChoosePixelFormatARB( winDC,(const s32*)pfAttr, NULL, 1, &pixelFormat, &count);

			if (count == 0)
			{
				Destroy();
				return false;
			}

			s32 pbAttr[] =
			{
				WGL_TEXTURE_FORMAT_ARB, WGL_TEXTURE_RGBA_ARB, // Our p-buffer will have a texture format of RGBA
				WGL_TEXTURE_TARGET_ARB, WGL_TEXTURE_2D_ARB,   // Of texture target will be GL_TEXTURE_2D
				0                                             // Zero terminates the list
			};

			pixelBuffer  = wglCreatePbufferARB(winDC, pixelFormat, bufferDim.width, bufferDim.height, pbAttr);
			pbufferDC    = wglGetPbufferDCARB(pixelBuffer);
			pbufferOGLRC = wglCreateContext(pbufferDC);

			if (!pixelBuffer)
			{
				Destroy();
				return false;
			}

			s32 h, w;
			wglQueryPbufferARB(pixelBuffer, WGL_PBUFFER_WIDTH_ARB, &h);
			wglQueryPbufferARB(pixelBuffer, WGL_PBUFFER_WIDTH_ARB, &w);

			if (h != bufferDim.height || w != bufferDim.width)
			{
				Destroy();
				return false;
			}

			// Share VBO between Window render context and pbuffer context
			if (!wglShareLists(winOGLRC, pbufferOGLRC))
			{
				Destroy();
				return false;
			}

			// Setup openGL with our pixelbuffer, first make the buffer the current render target
			// TODO: All this needed here???

			if (!wglMakeCurrent(pbufferDC, pbufferOGLRC)) 
			{
				Destroy();
				return false;
			}

			glShadeModel(GL_SMOOTH);
			glClearColor(0.0f, 0.0f, 0.7f, 0.8f); // TODO: Clear color is too hardcoded
			glClearDepth(1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

			if (!wglMakeCurrent(winDC, winOGLRC))
			{
				Destroy();
				return false;
			}

			return true;
		}

		bool Win32OGLPixelBuffer::SetBufferAsRenderTarget()
		{
			s32 flag = 0;
			wglQueryPbufferARB(pixelBuffer, WGL_PBUFFER_LOST_ARB, &flag);

			if (flag != 0)
			{
				Destroy();
				return false;
			}

			if (!wglMakeCurrent(pbufferDC, pbufferOGLRC)) 
			{
				Destroy();
				return false;
			}

			return true;
		}

		bool Win32OGLPixelBuffer::SetWindowAsRenderTarget()
		{
			if (!wglMakeCurrent(winDC, winOGLRC))
			{
				Destroy();
				return false;
			}

			return true;
		}

		bool Win32OGLPixelBuffer::BindBufferToTexture()
		{
			if (!wglBindTexImageARB(pixelBuffer, WGL_FRONT_LEFT_ARB))
			{
				Destroy();
				return false;
			}

			return true;
		}

		bool Win32OGLPixelBuffer::ReleaseBufferFromTexture()
		{
			if (!wglReleaseTexImageARB(pixelBuffer, WGL_FRONT_LEFT_ARB))
			{
				Destroy();
				return false;
			}

			return true;
		}

		IPixelBuffer* CreatePixelBuffer(const Dimension2D<s32>& pbufferDim)
		{
			return new Win32OGLPixelBuffer(pbufferDim);
		}
	
	}
}

#endif
