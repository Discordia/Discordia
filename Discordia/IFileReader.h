#ifndef IFILE_READER_H_INCLUDED
#define IFILE_READER_H_INCLUDED

#include <string>
#include "Types.h"

using std::string;

namespace Discordia
{
	namespace IO
	{
		/**
		 *  Interface that all kinds of file readers should implement, they could be
		 *  just regular file readers, that reads files from disk or they could read files from
		 *  an zip-archive, or from memory.
		 */
		class IFileReader
		{
		public:
			virtual ~IFileReader() {}

			virtual bool Read(c8* buffer, u32 num) = 0;
			virtual void ReadWhileGood(c8* buufer, u32 num) = 0;
			virtual bool Seek(c8 offset, int dir) = 0;
			virtual s32 GetSize() = 0;
			virtual s64 GetStreamPos() = 0;
			virtual bool IsOpen() = 0;
			virtual string GetFileName() = 0;

		protected:
			IFileReader() {}
		};
	}
}

#endif