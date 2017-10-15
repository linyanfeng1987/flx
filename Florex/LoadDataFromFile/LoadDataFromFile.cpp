// LoadDataFromFile.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <tchar.h>

#include <time.h>
#include "PubFun.h"
#include "HisRateLoader.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CHisRateLoader loader;
	string path = "F:\\florexData\\2017-9-3";
	map<string, string> files;
	PubFun::getFileByPath(path, files);
	int nIndex = 0;
	string file = "";
	string filePath = "";
	string fileExt = "";
	for ( pair<string,string> fileInfo : files )
	{
		file = fileInfo.first;
		filePath = fileInfo.second;

		nIndex = file.rfind('.');
		if ( -1 != nIndex )
		{
			fileExt = file.substr(nIndex+1);
			if (fileExt == "txt")
			{
				loader.load(filePath);
			}
		}
	}
	return 0;
}

