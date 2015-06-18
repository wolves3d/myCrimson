#include "pch.h"
#include "enemy.h"
#include "projectile.h"
#include "game_logic.h"
#include "ai/wandering_task.h"


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
	const float enemyRadiusSq = (32 * 32);

	// FIXME: fast bullets can walh through
	if (enemyRadiusSq > getPosition().getDistanceSq(projectile->getPosition()))
	{
		// hit!
		g_GameLogic->OnEnemyHit(this, projectile);
		return true;
	}

	return false;
}