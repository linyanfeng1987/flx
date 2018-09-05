#pragma once
#include "table/TableStruct.h"

class CTestDbInfoStruct;
typedef shared_ptr<CTestDbInfoStruct> PTestDbInfoStruct;

class CTestDbInfoStruct : public CTableStruct
{
protected:
	CTestDbInfoStruct();
public:
	static PTestDbInfoStruct instence();
	~CTestDbInfoStruct();

	static string key_id;
	static string key_value;
	
};

