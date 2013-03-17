#ifndef ILOG_TARGET_H_INCLUDED
#define ILOG_TARGET_H_INCLUDED

#include <string>
#include "Types.h"

using std::string;

namespace Discordia
{
	enum LogLevel
	{
		LOG_CRITICAL = 0,
		LOG_ERROR,
		LOG_DEBUG,	
		LOG_INFO
	};

	/**
	 *  Interface for a logger target. A logger target is a class that outputs log messages
	 *  into some forum. Could be a text file, or mayby a html file, or in a console window, or
	 *  prehaps a in game GUI Quad, you name it.
	 */
	class ILogTarget
	{
	public:
		virtual ~ILogTarget() {}
		
		virtual void		Log(string logString, LogLevel ll) = 0;
		virtual LogLevel	GetLogLevel() { return logLevel; }
		virtual void		SetLogLevel(LogLevel ll) {logLevel = ll; }

	protected:
		ILogTarget()
			: logLevel(LOG_DEBUG) {}

		LogLevel logLevel;
	};
}

#endif