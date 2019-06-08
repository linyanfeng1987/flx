#pragma once
#include <list>

#include "basePipelineNode.h"

using namespace std;

// º∆À„pipeline
class CCalcPipeline
{
public:
	CCalcPipeline(){}
	virtual ~CCalcPipeline(){}
	virtual PRateValue add(PRateValue rateValue);

	void puchBack(PBasePipelineNode node){nodes.push_back(node);}
	void clear(){nodes.clear();}
	
protected:
	list<PBasePipelineNode> nodes;	

};
typedef shared_ptr<CCalcPipeline> PCalcPipeline;
#define newCalcPipeline() make_shared<CCalcPipeline>()
