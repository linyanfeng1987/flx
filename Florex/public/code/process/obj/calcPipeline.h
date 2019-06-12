#pragma once
#include <list>

#include "basePipelineNode.h"

using namespace std;

// 计算pipeline
// 以后可能发展成树形结构，不过要xml读取做完
class CCalcPipeline
{
public:
	CCalcPipeline(){}
	virtual ~CCalcPipeline(){}
	virtual void add(PRateValue rateValue);

	void puchBack(PBasePipelineNode node){nodes.push_back(node);}
	void clear(){nodes.clear();}
	
protected:
	list<PBasePipelineNode> nodes;	

};
typedef shared_ptr<CCalcPipeline> PCalcPipeline;
#define newCalcPipeline() make_shared<CCalcPipeline>()
