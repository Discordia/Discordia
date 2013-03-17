#ifndef ISHADER_OBJECT_H_INCLUDED
#define ISHADER_OBJECT_H_INCLUDED

#include "Types.h"
#include "IFileReader.h"

namespace Discordia
{
	namespace Graphics
	{
		/** 
		 *	Interface that represents a shader, either a vertex or pixel shader.
		 */
		class IShaderObject
		{
		public:
			virtual ~IShaderObject() {}

			virtual u32		GetShaderId() = 0;
			virtual int		Compile(IO::IFileReader* fileReader) = 0;
			virtual bool	IsCompiled() = 0;

		protected:
			IShaderObject() {}
		};
	}
}

#endif