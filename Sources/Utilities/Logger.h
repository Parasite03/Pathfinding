#pragma once
class Logger
{
public:
	static void Trace(std::string string);
	static void Debug(std::string string);
	static void Info(std::string string);
	static void Warn(std::string string);
	static void Error(std::string string);
	static void Fatal(std::string string);
};

