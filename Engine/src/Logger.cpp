#include "Logger.h"
#include <cstdlib>
#include <format>
#include <chrono>
#include <sstream>

std::string Logger::m_logPath;

Logger::Logger()
{
	m_logPath = "logs/latest.txt";
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
	m_fileHandler.open(path);
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
	m_fileHandler.open(newPath);
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
	// Get current time
	auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* local = std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(local, "[%H:%M:%S]");
	std::string timeStr = oss.str();

	// String for return result
	std::string returnMessage = "";

	switch (type)
	{
	case Logger::INFO:
		returnMessage += timeStr + "[INFO]    " + msg + "\n";
		std::cout << returnMessage;
		break;
	case Logger::DEBUG:
		returnMessage += timeStr + "[DEBUG]   " + msg + "\n";
		std::cout << returnMessage;
		break;
	case Logger::WARNING:
		returnMessage += timeStr + "[WARNING] " + msg + "\n";
		std::cout << returnMessage;
		break;
	case Logger::ERROR:
		returnMessage += timeStr + "[ERROR]   " + msg + "\n";
		std::cout << returnMessage;
		break;
	default:
		returnMessage += timeStr + "[NULL]" + "\n";
		std::cout << returnMessage;
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