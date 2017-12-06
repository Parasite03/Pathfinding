#include "Logger.h"

void Logger::Trace(std::string string)
{
	std::cout << "[Trace] " << string << "\n";
}

void Logger::Debug(std::string string)
{
	std::cout << "[Debug] " << string << "\n";
}

void Logger::Info(std::string string)
{
	std::cout << "[Info] " << string << "\n";
}

void Logger::Warn(std::string string)
{
	std::cout << "[Warning] " << string << "\n";
}

void Logger::Error(std::string string)
{
	std::cout << "[Error] " << string << "\n";
}

void Logger::Fatal(std::string string)
{
	std::cout << "[Fatal] " << string << "\n";
}
