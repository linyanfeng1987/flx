#include "continueObj.h"
#include <map>
using namespace std;

// 连续的值
class CContinues
{
public:
	CContinues();

	void add(const CRateValue& curValue);
	long addContinueObj(PContinueObj);
protected:
	map<long, PContinueObj> continues;
};

typedef shared_ptr<CContinues> PContinuesj;
#define newContinues() make_shared<CContinues>();