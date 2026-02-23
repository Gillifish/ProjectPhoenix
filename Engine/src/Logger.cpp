#include "Logger.h"
#include <cstdlib>

std::string Logger::m_logPath;

Logger::Logger()
{
	m_logPath = "logs/log.txt";
	fileInit(m_logPath);
}

Logger* Logger::_instance = 0;
std::ofstream Logger::m_fileHandler;

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
	m_fileHandler.open(path, std::ios::app);
	if (!m_fileHandler.is_open())
	{
		std::cerr << "Failed to open log file at " << path << std::endl;
		exit(1);
	}

	logToConsole(Logger::INFO, "Successfully opened log file.");
}

void Logger::changeLogPath(std::string newPath)
{
	// Close current file
	m_fileHandler.close();

	// Open new file
	m_logPath = newPath;
	m_fileHandler.open(newPath, std::ios::app);
	if (!m_fileHandler.is_open())
	{
		std::cerr << "Failed to open new log file at " << newPath << std::endl;
	}

	logToConsole(Logger::INFO, "Successfully changed log path to " + newPath);
}

void Logger::log(MSG_TYPE type, std::string msg)
{
	if (!m_fileHandler.is_open())
	{
		logToConsole(Logger::ERROR, "File is not open and cannot be written to.");
		std::cerr << "Closing program" << std::endl;
	}

	// Log to console
	std::string returnMessage = logToConsole(type, msg);

	// Save to file
	m_fileHandler << returnMessage;
}

std::string Logger::logToConsole(MSG_TYPE type, std::string msg)
{
	std::string returnMessage = "";

	switch (type)
	{
	case Logger::INFO:
		returnMessage += "[INFO] " + msg + "\n";
		std::cout << returnMessage;
		break;
	case Logger::DEBUG:
		returnMessage += "[DEBUG] " + msg + "\n";
		std::cout << returnMessage;
		break;
	case Logger::WARNING:
		returnMessage += "[WARNING] " + msg + "\n";
		std::cout << returnMessage;
		break;
	case Logger::ERROR:
		returnMessage += "[ERROR] " + msg + "\n";
		std::cout << returnMessage;
		break;
	default:
		break;
	}

	return returnMessage;
}

void Logger::destroy()
{
	if (m_fileHandler.is_open())
	{
		m_fileHandler.close();
	}
}