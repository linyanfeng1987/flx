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

	
	void load(string strName, string strType=typeString, bool bIsPk = false);
	
	bool isNumberType();
	string strType;
	bool bIsPk;
	string strName;
};

typedef shared_ptr<CField> PField;