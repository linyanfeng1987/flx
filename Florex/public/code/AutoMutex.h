#pragma once
#include <mutex>
#include <string>

using namespace std;
class CAutoMutex 
{
public:
	CAutoMutex(mutex *pMutex);
	~CAutoMutex(void);

protected:
	mutex *pMutex;
};

