#pragma once
#include <string>
#include <list>
#include <memory>
#include "ConstDef.h"

using namespace std;

class CField
{
public:
	CField()
	{
		load("defultName");
	}

	
	void load(string _strName, string _strType=typeString, bool _bIsPk = false, bool _isIndex = false);
	
	bool isNumberType();
	string strType;
	bool bIsPk;
	string strName;
	bool isIndex;
};

typedef shared_ptr<CField> PField;