#ifndef FILE_SYSTEM_H_INCLUDED
#define FILE_SYSTEM_H_INCLUDED

#include "IVirtualFileSystem.h"

namespace Discordia
{
	namespace IO
	{
		class FileSystem : public IVirtualFileSystem
		{
		public:
			FileSystem();
			~FileSystem();

			IFileReader* OpenReadOnly(string fileName);

		private:
			IFileReader* OpenReadOnlyFromDisk(string fileName);
		};
	}
}

#endif