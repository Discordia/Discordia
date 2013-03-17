#ifndef ILOGGER_H_INCLUDED
#define ILOGGER_H_INCLUDED

#include "ILogTarget.h"

namespace Discordia
{
	class ILogger
	{
	public:
		virtual ~ILogger() {}

		virtual void Log(string logString, LogLevel level = LOG_DEBUG) = 0;
		virtual void AddLogTarget(ILogTarget* logTarget) = 0;

	protected:
		ILogger() {}
	};
}

#endif