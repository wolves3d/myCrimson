#include "pch.h"
#include "enemy.h"
#include "projectile/projectile.h"
#include "game_logic.h"
#include "ai/wandering_task.h"
#include "animation.h"


Enemy::Enemy()
	: m_GridIndex(-1)
	, m_Radius(15)
	, m_Weight(0.1f)
{}


Enemy * Enemy::create(const char * SpriteName)
{
	Enemy * Result = new Enemy();
	if (NULL != Result)
	{
		if (true == Result->init())
		{
			Result->autorelease();

			CCSprite* pSprite = CCSprite::create(SpriteName);
			if (NULL != pSprite)
			{
				Result->addChild(pSprite);
			}

			return Result;
		}

		delete Result;
	}

	return NULL;
}


void Enemy::StartAI()
{
	BaseAI * wanderTask = WanderingTask::create();
	wanderTask->SetUnit(this);
}


bool Enemy::HitTest(Projectile * projectile)
{
	const float enemyRadiusSq = powf(GetRadius(), 2);

	// FIXME: fast bullets can walk through
	if (enemyRadiusSq > getPosition().getDistanceSq(projectile->getPosition()))
	{
		// hit!
		g_GameLogic->OnEnemyHit(this, projectile);
		return true;
	}

	return false;
}


void Enemy::OnDie()
{
	stopAllActions(); // Stop AI
	removeAllChildren(); // Remove any AI states

	Animation * DeathVFX = Animation::create();
	DeathVFX->setPosition(getPosition());
	g_Map->addChild(DeathVFX);

	DeathVFX->Play("ma-eff-elimination", CCCallFunc::create(this, callfunc_selector(Enemy::RemoveFromMap)), 8);
}


void Enemy::RemoveFromMap()
{
	runAction( CCSequence::createWithTwoActions(
		CCEaseSineOut::create(CCScaleTo::create(0.3f, 0)),
		CCRemoveSelf::create()));
}