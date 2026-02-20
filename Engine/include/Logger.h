#pragma once
#include <string>

class Logger
{
private:
	static Logger* _instance;
	std::string m_logPath = "logs/log.txt";

	static void fileInit(std::string path);

protected:
	Logger();
public:
	typedef enum 
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
	} MSG_TYPE;

	static Logger* getInstance();

	// Changes the write path of the log file
	static void changeLogPath(std::string newPath);

	// Logs a message to standard output and log file
	static void log(MSG_TYPE type, std::string msg);

	// Logs only to console
	static void logToConsole(MSG_TYPE type, std::string msg);

};
