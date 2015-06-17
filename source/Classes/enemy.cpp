#include "pch.h"
#include "enemy.h"
#include "projectile.h"
#include "game_logic.h"


bool Enemy::init()
{
	if (false != CCNode::init())
	{
		CCSprite* pSprite = CCSprite::create("enemy.png");
		if (NULL != pSprite)
		{
			addChild(pSprite);
			return true;
		}
	}

	return false;
}


bool Enemy::HitTest(Projectile * projectile)
{
	const float enemyRadiusSq = (32 * 32);

	if (enemyRadiusSq > getPosition().getDistanceSq(projectile->getPosition()))
	{
		// hit!
		g_GameLogic->OnEnemyHit(this, projectile);
		return true;
	}

	return false;
}