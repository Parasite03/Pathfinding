#include "FileBrowser.h"

#include "Windows.h"

FileBrowser::FileBrowser()
{

}

FileBrowser::~FileBrowser()
{

}

std::string FileBrowser::OpenFile(std::string window_title)
{
	char filename[MAX_PATH];

	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = window_title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		return std::string(filename);
	}

	return std::string();
}

std::string FileBrowser::SaveFile(std::string window_title)
{
	char filename[MAX_PATH];

	OPENFILENAMEA ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files (*.txt)\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = window_title.c_str();
	ofn.Flags = OFN_DONTADDTORECENT;

	if (GetSaveFileNameA(&ofn))
	{
		std::string path(filename);
		if (path.substr(path.size() - 4, path.size() - 1) != ".txt")
			path.append(".txt");
		return path;
	}

	return std::string();
}

