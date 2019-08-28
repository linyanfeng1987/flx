#pragma once
#include <string>
#include <memory>

using namespace std;
class CRateInfo
{
public:
	~CRateInfo(void) {}
	CRateInfo() {}

	string rateName;
};

typedef shared_ptr<CRateInfo> PRateInfo;
#define newRateInfo() make_shared<CRateInfo>()