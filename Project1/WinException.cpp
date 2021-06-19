#include "WinException.h"
#include <sstream>

WinException::WinException(int line, const char* file) :
	line(line),
	file(file)
{}

const char* WinException::what() const
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* WinException::GetType() const
{
	return "Win Exception";
}


int WinException::GetLine() const
{
	return line;
}

const std::string& WinException::GetFile() const
{
	return file;
}

std::string WinException::GetOriginString() const
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl << "[Line] " << line;
	return oss.str();
}