#ifndef TEXT_LOGGER_H_INCLUDED
#define TEXT_LOGGER_H_INCLUDED

#include <fstream>
#include "ILogTarget.h"

using std::fstream;
using std::endl;

#ifdef WIN32
#include <Windows.h>
#endif

namespace Discordia
{
	/** 
	 *	TextLogger, loggs messages to a text file.
	 */
	class TextLogger : public ILogTarget
	{
	public:
		TextLogger()
			: ILogTarget()
		{
			fout.open("TextLog.txt", std::ios::out);
		}

		void Log(string logString, LogLevel ll)
		{
			if (ll == LOG_ERROR)
				fout << "ERROR: ";

			fout << logString << endl;
		}

		virtual ~TextLogger() 
		{
			fout.close();
		}

	protected:
		fstream fout;

	};
}

#endif