#include "HisRateLoader.h"
#include "PubFun.h"
#include <fstream>
#include "rate/HisRate.h"


CHisRateLoader::CHisRateLoader(void)
{
}


CHisRateLoader::~CHisRateLoader(void)
{
}

bool CHisRateLoader::load( string file )
{
	ifstream fin;
	fin.open(file);
	list<string> readRes;

	bool bHasData = true;
	bool firstLine = true;
	while (true)
	{
		readRes.clear();
		bHasData = PubFun::readHisFile(fin, readRes);
		for (string line : readRes)
		{
			if (firstLine)
			{
				firstLine = false;
				continue;
			}
			this->loadLine(line);	
		}
		
		if (!bHasData)
		{
			break;
		}
	}
	fin.close();
	return true;
}

bool CHisRateLoader::loadLine( string line )
{
	static CDbObj& db = CDbObj::instance();
	HisRate hisRate;
	hisRate.loadByLine(line);

	string sql = hisRate.toSqlString();
	char logMsg[2048] = {0};
	memset(logMsg, 0, sizeof(logMsg));
	db.ExecuteSql(sql.c_str(), logMsg);
	return true;
}
