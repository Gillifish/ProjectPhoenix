#include "Logger.h"
#include <cstdlib>

Logger::Logger()
{
	fileInit(m_logPath);
}

Logger* Logger::_instance = 0;

Logger* Logger::getInstance() 
{
	if (_instance == 0)
	{
		_instance = new Logger;
		atexit([]{ delete _instance; _instance = nullptr; });
	}
	return _instance;
}

void Logger::fileInit(std::string path)
{

}

void Logger::log(MSG_TYPE type, std::string msg)
{
	// Format messsage: [TYPE] Content
}

void Logger::logToConsole(MSG_TYPE type, std::string msg)
{

}