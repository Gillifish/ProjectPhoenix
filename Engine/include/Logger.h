#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <format>

// Class for engine logging; follows Singleton pattern
class Logger
{
private:
	static Logger* _instance;			// Single static instance of logger
	static std::string m_logPath;		// Path for the default log file called latest.txt
	static std::ofstream m_fileHandler; // ofstream filehandler

	// Opens the default file
	static void fileInit(std::string path);

protected:
	Logger();
public:
	// Enum for message types
	typedef enum 
	{
		DEBUG,
		INFO,
		WARNING,
		ERROR,
	} MSG_TYPE;

	// Returns the static instance of the logger
	static Logger* getInstance();

	// Changes the write path of the log file
	static void changeLogPath(std::string newPath);

	// Logs a message to standard output and log file
	static void log(MSG_TYPE type, std::string msg);

	// Logs only to console
	static std::string logToConsole(MSG_TYPE type, std::string msg);

	// Closes file and frees any allocated resources
	static void destroy();
};
