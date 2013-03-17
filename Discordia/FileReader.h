#ifndef FILE_READER_H_INCLUDED
#define FILE_READER_H_INCLUDED

#include "IFileReader.h"
#include <fstream>

using std::ifstream;

namespace Discordia
{
	namespace IO
	{
		/**
		 *  Derived filereader that reads file from disk.	
		 */
		class FileReader : public IFileReader
		{
		public: 
			FileReader(string fileName);
			FileReader(string fileName, int openMode);
			virtual ~FileReader();

			bool Read(c8* buffer, u32 num);
			void ReadWhileGood(c8* buffer, u32 num);
			bool Seek(c8 offset, int dir);
			s32 GetSize();
			s64 GetStreamPos();	
			bool IsOpen();
			string GetFileName();

		private:
			ifstream inFile;
			s32 fileSize;
			string fileName;
		};
	}
}

#endif