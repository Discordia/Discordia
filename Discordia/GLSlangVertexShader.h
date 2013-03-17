#ifndef GLSLANG_VERTEX_SHADER_H_INCLUDED
#define GLSLANG_VERTEX_SHADER_H_INCLUDED

#include <gl/GLee.h>
#include "GLSlangShaderObject.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  GLSL vertex shader.	
		 */
		class GLSlangVertexShader : public GLSlangShaderObject
		{
		public:
			GLSlangVertexShader()
				: GLSlangShaderObject()
			{
				shaderId = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
			}

			virtual ~GLSlangVertexShader()
			{
				glDeleteObjectARB(shaderId);
			}
		};
	}
}

#endif