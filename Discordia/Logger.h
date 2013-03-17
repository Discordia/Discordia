#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
#include "ILogTarget.h"

using std::vector;
using std::shared_ptr;

namespace Discordia
{
	/**
	 *  Logger, multicast logger mesages to logger targets.	
	 */
	class Logger
	{
	public:
		Logger() 
		{
		}

		virtual ~Logger() 
		{
		}

		void Log(string logString, LogLevel level = LOG_DEBUG)
		{
			vector<shared_ptr<ILogTarget> >::iterator it;
			for (it = logTargets.begin(); it != logTargets.end(); it++)
			{
				if ((*it)->GetLogLevel() >= level)
					(*it)->Log(logString, level);
			}
		}

		void AddLogTarget(ILogTarget* logTarget)
		{
			logTargets.push_back(shared_ptr<ILogTarget>(logTarget));
		}

		virtual void RemoveLogTarget(ILogTarget* logTarget)
		{
			vector<shared_ptr<ILogTarget> >::iterator it = find(logTargets.begin(), logTargets.end(), shared_ptr<ILogTarget>(logTarget));
			logTargets.erase(it);
		}

	protected:
		vector<shared_ptr<ILogTarget> > logTargets;
	};
}

#endif