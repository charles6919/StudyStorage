#pragma once
#include "SingletonBase.h"

#define g_pFileManager FileManager::GetInstance()

class FileManager :
	public SingletonBase<FileManager>
{
private:


public:
	FileManager();
	~FileManager();

private:
	char* VectorArrayCombine(vector<string>& vecArray);
	vector<string> CharArraySeparation(char charArray[]);

public:
	void TxtSave(wstring saveFileName, vector<string>& vecData);
	vector<string> TxtLoad(wstring loadFileName);
};

