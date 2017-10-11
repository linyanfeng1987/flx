#pragma once
#include <string>
#include <map>
#include <list>

using namespace std;
class CField
{
public:
	CField()
	{
		strName = "defultName";
		strType = "string";
		bIsPk = false;
	}
	string strType;
	bool bIsPk;
	string strName;
};

