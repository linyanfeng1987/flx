#include <list>
#include <map>
#include "LinkedHashMap.h"

using namespace std;

class CRateValue
{
public:
	CRateValue(){
		time = 0;
		value = 0;
	}

	bool isValid() const{return time != 0;} 
	double time;
	double value;
};

const CRateValue zeroRateValue;
