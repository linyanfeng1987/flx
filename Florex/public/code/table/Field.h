#pragma once
#include <string>
#include <list>
#include <memory>

using namespace std;

class CField
{
public:
	CField()
	{
		load("defultName");
	}

	void load(string strName, string strType="string", bool bIsPk = false);
	string strType;
	bool bIsPk;
	string strName;
};

typedef shared_ptr<CField> PField;