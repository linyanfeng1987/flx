
#include "HisRate.h"
#include "PubFun.h"
#include <algorithm>



HisRate::HisRate(void)
{
	time = 0;
	timeStepType = timeStepStep_def;
	open = 0.0;
	high = 0.0;
	low = 0.0;
	close = 0.0;
	tick_volume = 0;
	spread = -1;
	real_volume = 0;
}


HisRate::~HisRate(void)
{
}

std::string HisRate::toString()
{
	char tmp[1024] = {0};
	sprintf_s(tmp, "time:%d, timeStepType:%d, open:%f, high:%f, low:%f, close:%f, tick_volume:%d, spread:%d, real_volume:%d",
		time, timeStepType, open,  high, low, close, tick_volume,  spread, real_volume);

	return string(tmp);
}

void HisRate::loadByLine( string line )
{
	//XAUUSD,20010102,231200,268.8000,268.8000,268.8000,268.8000,4
	string strDate = "";
	string strTime = "";
	char strName[128] = {0};
	list<string> strList = PubFun::split(line, ",");

	int nIndex = 1;
	for ( string strTmp : strList )
	{
		switch (nIndex)
		{
		case 1:
			transform(strTmp.begin(),strTmp.end(),strTmp.begin(),tolower);
			this->rateName = strTmp; 
			break;
		case 2:
			strDate = strTmp; 
			break;
		case 3:
			strTime = strTmp; 
			break;
		case 4:
			sscanf_s(strTmp.c_str(), "%lf", &(this->open));
			break;
		case 5:
			sscanf_s(strTmp.c_str(), "%lf", &(this->high));
			break;
		case 6:
			sscanf_s(strTmp.c_str(), "%lf", &(this->low));
			break;
		case 7:
			sscanf_s(strTmp.c_str(), "%lf", &(this->close)); 
			break;
		case 8:
			sscanf_s(strTmp.c_str(), "%d", &(this->real_volume)); 
			break;
		}
		nIndex++;
	}

	//sscanf_s(line.c_str(), "%s,%s,%s,%f,%f,%f,%f,%d", strName, strDate, strTime, &(this->open), &(this->high), &(this->low), &(this->close), &(this->real_volume));

	string strTmp = "";
	strTmp.append(strDate);
	strTmp.append(" ");
	strTmp.append(strTime);

	time_t t = PubFun::HisRateStringToDatetime(strTmp.c_str());

	
	this->time = (long int)t;
	this->timeFormat = PubFun::getTimeFormat(t);
	this->percentSpead_s = PubFun::calcPercentSpeadProS(this->time, 0, this->high, this->time+60, 0, this->low);
	this->timeStepType = timeStepStep_mm;
}

std::string HisRate::toSqlString()
{
	string strSqlFormat = "insert into %s ( startTime, openPrice, lowPrice, highPrice, closePrice, volume, timeFormat, percentSpead_s ) value \
						  ( %d, %.5f, %.5f, %.5f, %.5f, %d, \"%s\", %.5f);";
	string strTableName = "currency_pair_";
	strTableName += this->rateName;
	strTableName = dbName +"."+ strTableName;
	switch (this->timeStepType)
	{
	case timeStepStep_mm:
		strTableName += tableTimeStepEnd_mm;
		break;
	case timeStepStep_15m:
		strTableName += tableTimeStepEnd_15m;
		break;
	case timeStepStep_hh:
		strTableName += tableTimeStepEnd_hh;
		break;
	case timeStepStep_4h:
		strTableName += tableTimeStepEnd_4h;
		break;
	case timeStepStep_dd:
		strTableName += tableTimeStepEnd_dd;
		break;
	case timeStepStep_ww:
		strTableName += tableTimeStepEnd_ww;
		break;
	}

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str(), 
		this->time, this->open, this->low, this->high, this->close, this->real_volume, this->timeFormat.c_str(), this->percentSpead_s);

	return chSql;
}
