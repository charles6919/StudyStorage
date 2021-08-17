#include "stdafx.h"
#include "FileManager.h"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

char* FileManager::VectorArrayCombine(vector<string>& vecArray)
{
	char szBuf[1024];
	ZeroMemory(szBuf, sizeof(szBuf));
	

	//strcpy : 문자역 복사
	//strcat : 문자열 붙이기
	//strcmp : 문자열 비교
	for (int i = 0; i < vecArray.size(); i++)
	{
		strcat_s(szBuf, vecArray[i].c_str());

		if (i < vecArray.size() - 1)
			strcat_s(szBuf, ",");
	}

	return szBuf;
}

vector<string> FileManager::CharArraySeparation(char charArray[])
{
	vector<string> vecArray;
	const char* separator = ",";
	char* token = NULL;
	char* remained = NULL;

	token = strtok_s(charArray, separator, &remained);
	if (token != NULL)
		vecArray.push_back(token);

	while ((token = strtok_s(remained, separator, &remained)) != NULL)
	{
		vecArray.push_back(token);		
	}

	return vecArray;
}

void FileManager::TxtSave(wstring saveFileName, vector<string>& vecData)
{
	HANDLE file;
	char szBuf[1024];
	DWORD write;

	strncpy_s(szBuf, 1024, VectorArrayCombine(vecData), 1022);

	wstring fullPath = L"../../_Files/" + saveFileName + L".txt";

	file = CreateFile(fullPath.c_str(),
		GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, szBuf, strlen(szBuf), &write, NULL);

	CloseHandle(file);

}

vector<string> FileManager::TxtLoad(wstring loadFileName)
{
	HANDLE file;
	char szBuf[1024];
	DWORD read;

	ZeroMemory(szBuf, sizeof(szBuf));

	wstring fullPath = L"../../_Files/" + loadFileName + L".txt";

	file = CreateFile(fullPath.c_str(),
		GENERIC_READ, NULL, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, szBuf, 1024, &read, NULL);

	CloseHandle(file);

	return CharArraySeparation(szBuf);
}
