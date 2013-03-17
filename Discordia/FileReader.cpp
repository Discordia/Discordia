#include "FileReader.h"

namespace Discordia
{
	namespace IO
	{
		FileReader::FileReader(string fileName)
			: IFileReader(), fileSize(0)
		{
			if (fileName.length() != 0)
			{
				inFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
			}

			if (inFile)
			{
				this->fileName = fileName;
				inFile.seekg(0, std::ios::end);
				fileSize = inFile.tellg();
				inFile.seekg(0, std::ios::beg);
			}
		}

		FileReader::FileReader(string fileName, int openMode)
			: IFileReader(), fileSize(0)
		{
			if (fileName.length() != 0)
			{
				inFile.open(fileName.c_str(), openMode);
			}

			if (inFile)
			{
				this->fileName = fileName;
				inFile.seekg(0, std::ios::end);
				fileSize = inFile.tellg();
				inFile.seekg(0, std::ios::beg);
			}
		}

		FileReader::~FileReader()
		{
			inFile.close();
		}

		bool FileReader::Read(c8* buffer, u32 num)
		{
			inFile.read(buffer, num);
			return inFile.good();
		}

		void FileReader::ReadWhileGood(c8* buffer, u32 num)
		{
			u32 i = 0;
			while(inFile.good())
			{
				buffer[i++] = inFile.get();

				if (i > num) 
					i = num;
			}

			buffer[i] = 0;
		}

		bool FileReader::Seek(c8 offset, int dir)
		{
			inFile.seekg(offset, dir);
			return inFile.good();
		}

		s32 FileReader::GetSize()
		{
			return fileSize;
		}

		s64 FileReader::GetStreamPos()
		{
			return inFile.tellg();
		}

		bool FileReader::IsOpen()
		{
			return inFile != 0;
		}

		string FileReader::GetFileName()
		{
			return fileName;
		}
	}
}