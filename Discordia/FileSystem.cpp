#include "FileSystem.h"
#include "FileReader.h"

namespace Discordia
{
	namespace IO
	{
		FileSystem::FileSystem()
		{

		}

		FileSystem::~FileSystem()
		{

		}

		IFileReader* FileSystem::OpenReadOnly(string fileName)
		{
			return OpenReadOnlyFromDisk(fileName);
		}

		IFileReader* FileSystem::OpenReadOnlyFromDisk(string fileName)
		{
			return new FileReader(fileName);
		}


	}
}