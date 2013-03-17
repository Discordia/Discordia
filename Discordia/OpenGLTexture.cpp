#include "OpenGLTexture.h"

namespace Discordia
{
	namespace Graphics
	{
		OpenGLTexture::OpenGLTexture(ISurface* surface)
			: textureId(0)
		{
			if (!surface)
				return;

			int texType = GL_RGB;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);
			
			if (surface->GetBytes() == 4)
				texType = GL_RGBA;

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			gluBuild2DMipmaps(GL_TEXTURE_2D, surface->GetBytes(), surface->GetDimension().width,
				surface->GetDimension().height, texType, GL_UNSIGNED_BYTE, surface->Lock());

			surface->Unlock();
		}

		OpenGLTexture::OpenGLTexture(const Dimension2D<s32>& textureDim)
		{
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			// TODO: mipmapping?? Parameter if we want mipmaping?? GL_RGB or parameter with COLOR_FORMAT??
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureDim.width, textureDim.height, 
				0, GL_RGB, GL_FLOAT, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		}

		OpenGLTexture::~OpenGLTexture()
		{
			glDeleteTextures(1, &textureId);
		}

	}
}