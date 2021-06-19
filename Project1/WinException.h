#pragma once
#include<exception>
#include<string>

class WinException : public std::exception
{
public:
	WinException(int line, const char* file);
	const char* what() const override;
	virtual const char* GetType() const;
	int GetLine() const;
	const std::string& GetFile() const;
	std::string GetOriginString() const;
private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;
};
