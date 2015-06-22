#include "pch.h"
#include "player.h"
#include "wandering_task.h"
#include "game_logic.h"



WanderingTask::WanderingTask()
	: m_IsFixingRotation(false)
{
}


void WanderingTask::OnBegin()
{
	GoSomewhere();
	scheduleUpdate();
}


void WanderingTask::update(float delta)
{
	g_GameLogic->OnEnemyMoved(GetUnit());

	if (false == m_IsFixingRotation)
	{
		Unit * UnitNode = GetUnit();

		if (UnitNode->getRotation() > 0)
		{
			m_IsFixingRotation = true;

			CCSequence * ActionSequence = CCSequence::create(CCArray::create(
				CCDelayTime::create(RND_INTERVAL(0.5f, 1.0f)),
				CCRotateTo::create(1.5f, 0),
				CCCallFunc::create(this, callfunc_selector(WanderingTask::OnFeet)),
				NULL));

			UnitNode->runAction(ActionSequence);
		}
	}
}


void WanderingTask::OnFeet()
{
	m_IsFixingRotation = false;
}


void WanderingTask::OnSubTaskEnded(BaseAI * subTask)
{
	GoSomewhere();
}


void WanderingTask::GoSomewhere()
{
	const float radius = 50;
	const CCPoint enemyPos(GetUnit()->getPosition());

	const CCPoint vectorToPlayer = ccpMult(
		ccpSub(g_Player->getPosition(), enemyPos).normalize(),
		0.25f * radius);

//	const CCPoint vectorToPlayer(CCPointZero);

	CCPoint nextTarget = ccpAdd(enemyPos, vectorToPlayer);
	nextTarget.x += ((((float)rand() / 32768.f) - 0.5f) * radius);
	nextTarget.y += ((((float)rand() / 32768.f) - 0.5f) * radius);

	BaseAI * moveTask = BaseAI::create();
	AddSubTask(moveTask);

	moveTask->MoveTo(nextTarget);
}
