#ifndef IVIRTUAL_FILE_SYSTEM_H_INCLUDED
#define IVIRTUAL_FILE_SYSTEM_H_INCLUDED

#include <string>
#include "IFileReader.h"

using std::string;

namespace Discordia
{
	namespace IO
	{
		/**
		 *  Begining to a virtual filesystem, should be extended so that file can be loaded from
		 *  a numerus of places and abstract that so anyone how laods do not have to now where the
		 *  file they want to load is localed (in archive, on disk or from a CD).
		 */
		class IVirtualFileSystem
		{
		public:
			virtual ~IVirtualFileSystem() {}

			virtual IFileReader* OpenReadOnly(string fileName) = 0;
		
		protected: 
			IVirtualFileSystem() {}
		};
	}
}

#endif