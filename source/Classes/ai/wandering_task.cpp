#include "pch.h"
#include "wandering_task.h"


void WanderingTask::OnBegin()
{
	GoSomewhere();
}


void WanderingTask::OnSubTaskEnded(BaseAI * subTask)
{
	GoSomewhere();
}


void WanderingTask::GoSomewhere()
{
	const float radius = 100;

	Unit * unit = GetUnit();
	CCPoint nextTarget = unit->getPosition();
	nextTarget.x += ((((float)rand() / 32768.f) - 0.5f) * radius);
	nextTarget.y += ((((float)rand() / 32768.f) - 0.5f) * radius);

	BaseAI * moveTask = BaseAI::create();
	AddSubTask(moveTask);

	moveTask->MoveTo(nextTarget);
}
