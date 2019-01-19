#include "process/obj/rateValue.h"
#include <memory.h>


using namespace std;

// 连续的值
class CContinueValue
{
public:
	CContinueValue();


	CRateValue startValue;
	CRateValue endValue;

	// 停止相关信息
	CRateValue stopValue;
	// 停止的判断信息，类型暂定
	string stopType;
	double stopValue;
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>();