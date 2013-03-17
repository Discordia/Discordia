#include <gl/GLee.h>
#include "GLSlangShaderObject.h"

namespace Discordia
{
	namespace Graphics
	{
		GLSlangShaderObject::GLSlangShaderObject()
			: IShaderObject(), isCompiled(false)
		{
		}

		GLSlangShaderObject::~GLSlangShaderObject()
		{
		}

		int GLSlangShaderObject::Compile(IO::IFileReader* fileReader)
		{
			s32 compiled;
			u8* assembly = (u8*) new c8[fileReader->GetSize()];
			assembly[fileReader->GetSize()] = 0;
			isCompiled = false;

			fileReader->ReadWhileGood((c8*)assembly, fileReader->GetSize());
			glShaderSourceARB(shaderId, 1, (const GLcharARB**)&assembly, 0);
			glCompileShaderARB(shaderId);

			glGetObjectParameterivARB( shaderId, GL_OBJECT_COMPILE_STATUS_ARB, &compiled);

			if (compiled)
				isCompiled = true;

			return compiled;
		}

		bool GLSlangShaderObject::IsCompiled()
		{
			return isCompiled;
		}

	}
}