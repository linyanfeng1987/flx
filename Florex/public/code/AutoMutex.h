#pragma once
#include <mutex>
#include <string>
#include "LogObj.h"

using namespace std;
class CAutoMutex
{
public:
	CAutoMutex(recursive_mutex* pMutex);
	~CAutoMutex(void);

protected:
	recursive_mutex* pMutex;
};
