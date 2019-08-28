#pragma once
#include <list>
#include <map>
#include "process/obj/rateValue.h"
#include "continueValue.h"
#include "LinkedHashMap.h"
#include <memory>

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
// 6. 参与成员：CContinueJudgeObj：连续记录，保持，成长
//				标准对象组：对象生成，存储，切换
//				标准对象：判断起始连续，中断，成长标准（不可直接被外部访问，仅仅拿到level）
//				builder：标准的集合？初始连续判断+obj生成
//				continus：多个obj的存储

enum emumContinueStatus
{
	continue_stop = -1,  // 中断
	continue_lowDown,	// 降级
	continue_keep,		// 保持（未增长）
	continue_groupUp	// 增长
};

class CContinueJudgeObj
{
public:
	CContinueJudgeObj(int continueLevel);

	static double getStepPersent(PRateValue curValue, PRateValue startValue);

	void init(double minStepValuePersent, double retrcementValue, double retrcementSpead);

	bool isContinueStart_s(const PRateValue curValue, PRateValue startValue);
	bool isContinueStart(double& stepPersent);
	//emumContinueStatus isContinueGoOn(PRateValue curValue, PRateValue startValue, PRateValue tryEndValue, int& curDirect, double& curRetrcementSpead, PContinueValue& pContinueValue);
	emumContinueStatus isContinueGoOn(PRateValue curValue, PContinueValue pContinueValue);

	bool isLowDown(double& curRetrcementSpead);
	int getLevel() { return continueLevel; }
protected:
	bool add(const PRateValue curValue, PRateValue startValue, PRateValue tryEndValue, int& curDirect);

	// 停止连续，记录连续，并尝试校验新的连续
	//bool stopContinue(PRateValue stopValue, PRateValue startValue, PRateValue tryEndValue);

	// 连续等级
	int continueLevel;

	// 必须达到最小便宜比例，才算在此区间上连续, 单位：千分比
	double minStepValuePersent;
	//double minStepSpeedPersent;
	//////////////////////////////////////////////////////////////////////////
	// 连续判断变量
	// 回撤值，当回撤小于次值认为连续未中断，否则认为连续终端
	double retrcementValue;
	// 从起始值算起，最小速率，单位 s?h？
	//double stopSpead;
	// 回撤速率 用于降低连续等级
	double retrcementSpead;
};

typedef shared_ptr<CContinueJudgeObj> PContinueJudgeObj;
#define newContinueJudgeObj(T) make_shared<CContinueJudgeObj>(T)