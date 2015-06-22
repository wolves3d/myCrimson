#include "pch.h"
#include "projectile.h"
#include "game_logic.h"


bool Projectile::init()
{
	if (false == CCNode::init())
		return false;

	CCSprite* pSprite = CCSprite::create("bullet_bill_yids.png");

	if (NULL == pSprite)
	{
		return false;
	}

	addChild(pSprite);
	return true;
}


void Projectile::Go(CCPoint target, float speed, float maxDistance)
{
	CCPoint targetDir = ccpSub(target, getPosition());
	const float shootDistance = targetDir.getLength();

	// Set start projectile rotation
	targetDir = targetDir.normalize();
	const float angle = -atan2f(targetDir.y, targetDir.x);
	setRotation(RADIAN_TO_DEGREE(angle));	

	const float flyTime = (shootDistance / speed);

	// Override target
	target = ccpAdd(getPosition(), ccpMult(targetDir, maxDistance));

	CCAction * action = CCSequence::createWithTwoActions(
		CCMoveTo::create(flyTime, target),
		CCCallFunc::create(this, callfunc_selector(Projectile::OnMissed)));

	if (NULL != action)
	{
		runAction(action);
	}
}


void Projectile::OnMissed()
{
	g_GameLogic->OnRemoveUnit(this);
}