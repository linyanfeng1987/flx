#pragma once
#include "continueObj.h"
#include <map>
using namespace std;
// 连续有个起点A
// 连续有方向 
// 连续的判定？1回撤的幅度？

// 在一定时间段，一个方向上，连续？
// 起始点的判断？上一个的终点？那不同的阈值将决定不同的终点？
// 尝试多个阈值？ 阈值的准确性？ 
// 连续方向的切换平率？
// 如何定义方向的正确性？
// 是否分类统计？manager？ 先不设置manager试试


// 寻找最小连续的obj，并生成对象
class CContinueFinder
{
public:
	CContinueFinder(PContinueJudgeGroup pJudgeGroup);

	bool add(PRateValue curValue);
	
	void init();

	void setId(long finderId){this->finderId = finderId;}
	long getId(){ return finderId;}
protected:

	long finderId;

	void tryFindNew(PRateValue curValue);
	void addToObj(PRateValue curValue);
	// 方向 +1 或 -1
	//map<int, CRateValue> flagValue;
	//int curContinueDirect;
	PRateValue startValue;

	long objIndex;

	// 只存在两个连续对象，一个方向一个
	map<int, PContinueObj> curObjs;
	map<long, PContinueObj> hisObjs;
	PContinueJudgeGroup pJudgeGroup;
};

typedef shared_ptr<CContinueFinder> PContinueFinder;
#define newContinueFinder(T) make_shared<CContinueFinder>(T)