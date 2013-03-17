#ifndef GLSLANG_SHADER_OBJECT_H_INCLUDED
#define GLSLANG_SHADER_OBJECT_H_INCLUDED

#include "IShaderObject.h"

namespace Discordia
{
	namespace Graphics
	{
		/**
		 *  Common base class for GLSL shaders, compiles shaders.	
		 */
		class GLSlangShaderObject : public IShaderObject
		{
		public:
			virtual ~GLSlangShaderObject();

			u32 GetShaderId() { return shaderId; }
			int Compile(IO::IFileReader* fileReader);
			bool IsCompiled();

		protected:
			GLSlangShaderObject();

		protected:
			u32 shaderId;
			bool isCompiled;
		};
	}
}


#endif