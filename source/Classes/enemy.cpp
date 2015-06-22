#include "pch.h"
#include "enemy.h"
#include "projectile/projectile.h"
#include "game_logic.h"
#include "ai/wandering_task.h"


Enemy::Enemy()
	: m_GridIndex(-1)
{}


bool Enemy::init()
{
	if (false != CCNode::init())
	{
		CCSprite* pSprite = CCSprite::create("enemy.png");
		if (NULL != pSprite)
		{
			addChild(pSprite);
		}

		return true;
	}

	return false;
}


void Enemy::StartAI()
{
	BaseAI * wanderTask = WanderingTask::create();
	wanderTask->SetUnit(this);
}


bool Enemy::HitTest(Projectile * projectile)
{
	const float enemyRadiusSq = powf(GetRadius(), 2);

	// FIXME: fast bullets can walh through
	if (enemyRadiusSq > getPosition().getDistanceSq(projectile->getPosition()))
	{
		// hit!
		g_GameLogic->OnEnemyHit(this, projectile);
		return true;
	}

	return false;
}