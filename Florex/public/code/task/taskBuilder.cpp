#include "taskBuilder.h"

CTaskBuilder::CTaskBuilder()
{
}

CTaskBuilder::~CTaskBuilder()
{
}

void CTaskBuilder::run()
{
	for (string rateName : rateNames)
	{
		runOneRate(rateName);
	}
}

void CTaskBuilder::runOneRate( string rateName )
{

}
