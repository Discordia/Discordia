#ifndef OPENGL_TEXTURE_H_INCLUDED
#define OPENGL_TEXTURE_H_INCLUDED

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "ITexture.h"
#include "ISurface.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  OpenGL texture wrapper, holds the texture handle.
		 */
		class OpenGLTexture : public ITexture
		{
		public:
			OpenGLTexture(ISurface* surface);
			OpenGLTexture(const Dimension2D<s32>& textureDim);
			virtual ~OpenGLTexture();

			u32 GetTextureID() { return textureId; }
			bool IsCreated() { return glIsTexture(textureId) == GL_TRUE; }

		protected:
			u32	textureId;
		};
	}
}

#endif