#include "pch.h"
#include "base_ai.h"


BaseAI::BaseAI()
	: m_ParentTask(NULL)
	, m_Unit(NULL)
{
}


BaseAI * BaseAI::create(Unit * parentUnit)
{
	BaseAI * result = new BaseAI();
	if (NULL != result)
	{
		if (true == result->init())
		{
			result->autorelease();
			result->SetUnit(parentUnit);

			return result;
		}
		
		delete result;
	}

	return NULL;
}


void BaseAI::SetUnit(Unit * unit)
{
	if (NULL == m_Unit)
	{
		m_Unit = unit;

		if (NULL == getParent())
		{
			m_Unit->addChild(this);
		}

		OnBegin();
	}
	else
	{
		CC_ASSERT(!"Unit override not allowed!");
	}
}


void BaseAI::AddSubTask(BaseAI * subTask)
{
	subTask->m_ParentTask = this;
	addChild(subTask);
	subTask->SetUnit(GetUnit());
}

void BaseAI::OnEndReserved()
{
	if (NULL != m_ParentTask)
	{
		m_ParentTask->OnSubTaskEnded(this);
	}

	OnEnd();

	removeFromParent();
}


void BaseAI::MoveTo(const CCPoint & target)
{
	stopAllActions();

	CCPoint curPosition = GetUnit()->getPosition();

	CCPoint targetVector = ccpSub(target, curPosition);
	const float moveDistance = targetVector.getLength();
	const float moveTime = (moveDistance / 50.0f);

	/*
	// Set start projectile rotation
	targetDir = targetDir.normalize();
	const float angle = -atan2f(targetDir.y, targetDir.x);
	setRotation(RADIAN_TO_DEGREE(angle));

	const float flyTime = (shootDistance / speed);

	// Override target
	target = ccpAdd(getPosition(), ccpMult(targetDir, maxDistance));
	*/

	CCAction * action = CCSequence::createWithTwoActions(
		CCMoveTo::create(moveTime, target),
		CCCallFunc::create(this, callfunc_selector(BaseAI::OnArrived)));

	if (NULL != action)
	{
		GetUnit()->runAction(action);
	}
}


void BaseAI::OnArrived()
{
	OnEndReserved();
}