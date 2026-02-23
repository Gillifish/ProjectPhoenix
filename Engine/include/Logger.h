#pragma once
#include <string>
#include <iostream>
#include <fstream>

class Logger
{
private:
	static Logger* _instance;
	static std::string m_logPath;
	static std::ofstream m_fileHandler;

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
	static std::string logToConsole(MSG_TYPE type, std::string msg);

	static void destroy();
};
