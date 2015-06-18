#include "pch.h"
#include "player.h"
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
	const CCPoint enemyPos(GetUnit()->getPosition());
	const CCPoint vectorToPlayer = ccpMult(
		ccpSub(g_Player->getPosition(), enemyPos).normalize(),
		0.25f * radius);

	CCPoint nextTarget = ccpAdd(enemyPos, vectorToPlayer);
	nextTarget.x += ((((float)rand() / 32768.f) - 0.5f) * radius);
	nextTarget.y += ((((float)rand() / 32768.f) - 0.5f) * radius);

	BaseAI * moveTask = BaseAI::create();
	AddSubTask(moveTask);

	moveTask->MoveTo(nextTarget);
}
