#pragma once
#include <list>
#include <map>
#include "process/obj/rateValue.h"
#include "continueValue.h"
#include "LinkedHashMap.h"
#include <memory>
#include "continueJudgeGroup.h"

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

// 思路：
// 1. 要完成成长，记录成长过程，
// 2. 那就要知道成长的标准
// 3. 是否存在合并这一说？合并的原则？时间连续，方向连续，前者中断？合并逻辑较为困难
// 4. 还是走成长这个模拟思路较好
// 5. 成长的标准，度量队列？
// 6. 参与成员：CContinueObj：连续记录，保持，成长
//				标准对象组：对象生成，存储，切换
//				标准对象：判断起始连续，中断，成长标准（不可直接被外部访问，仅仅拿到level
//				builder：标准的集合？初始连续判断+obj生成
//				continus：多个obj的存储


class CContinueSubsection
{
public:
	CContinueSubsection(PContinueJudgeGroup pJudgeGroup);
	void init(PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& judegLevel);

	void setSectionId(long sectionId){this->sectionId = sectionId;}
	long getSectionId(){ return sectionId;}

	emumContinueStatus isContinueGoOn(PRateValue curValue);

	void CContinueSubsection::stopContinue(PRateValue curValue);

	PContinueValue getContinueValue(){return pContinueValue;}

	PContinueJudgeGroup getJudgeGroup(){return pJudgeGroup;}

	int getCurLevel(){return curLevel;}
protected:
	long sectionId;

	// 方向 +1 或 -1
	int curDirect;
	PRateValue startValue;
	// 同方向最远的值
	PRateValue tryEndValue;
	int maxLevel;
	// 连续等级 
	int curLevel;
	// 上次上报的值
	//CRateValue lastValue;
	list<int> levelStep;
	emumContinueStatus curStatus;

	PContinueValue pContinueValue;
	PContinueJudgeGroup pJudgeGroup;
};

typedef shared_ptr<CContinueSubsection> PContinueSubsection;
#define newContinueSubsection(T) make_shared<CContinueSubsection>(T)