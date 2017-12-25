#pragma once

class FileBrowser
{
private:
	FileBrowser();
	~FileBrowser();

public:
	static std::string OpenFile(std::string window_title);
	static std::string SaveFile(std::string window_title);
};

