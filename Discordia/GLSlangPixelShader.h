#ifndef GLSLANG_PIXEL_SHADER_H_INCLUDED
#define GLSLANG_PIXEL_SHADER_H_INCLUDED

#include <gl/GLee.h>
#include "GLSlangShaderObject.h"

namespace Discordia
{
	namespace Graphics
	{
		/** 
		 *	GLSL pixel (ragment) shader.
		 */
		class GLSlangPixelShader : public GLSlangShaderObject
		{
		public:
			GLSlangPixelShader()
				: GLSlangShaderObject()
			{
				shaderId = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
			}

			virtual ~GLSlangPixelShader()
			{
				glDeleteObjectARB(shaderId);
			}
		};
	}
}

#endif