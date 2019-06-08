#include "calcPipeline.h"

PRateValue CCalcPipeline::add( PRateValue rateValue )
{
	PRateValue tempValue = rateValue;
	for (PBasePipelineNode node : nodes)
	{
		tempValue = node->add(tempValue);
	}
}
