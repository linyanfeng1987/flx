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
	printf("load file:%s\n", file.c_str());
	ifstream fin;
	fin.open(file);
	list<string> readRes;

	bool bHasData = true;
	bool firstLine = true;
	static CDbObj& db = CDbObj::instance();
	HisRate hisRate;
	string sql = "";
	list<string> sqls;
	while (true)
	{
		readRes.clear();
		bHasData = PubFun::readHisFile(fin, readRes);
		printf("deal with:%s\n",(*(readRes.begin())).c_str());

		sqls.clear();
		for (string line : readRes)
		{
			if (firstLine)
			{
				firstLine = false;
				continue;
			}
			
			hisRate.loadByLine(line);
			sql = hisRate.toSqlString();
			sqls.push_back(sql);
		}
		db.insertDatas(sqls);
		
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

	db.executeSql(sql.c_str());
	return true;
}
