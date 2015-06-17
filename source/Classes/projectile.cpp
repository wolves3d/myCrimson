#include "pch.h"
#include "projectile.h"


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
	scheduleUpdate();
	return true;
}


void Projectile::Go(const CCPoint & target)
{
	// Set start projectile rotation
	const CCPoint targetDir = ccpNormalize(ccpSub(target, getPosition()));
	const float angle = -atan2f(targetDir.y, targetDir.x);
	setRotation(RADIAN_TO_DEGREE(angle));	

	CCAction * action = CCSequence::createWithTwoActions(
		CCMoveTo::create(0.1f, target),
		CCCallFunc::create(this, callfunc_selector(Projectile::OnMissed)));

	if (NULL != action)
	{
		runAction(action);
	}
}


void Projectile::update(float delta)
{

}


void Projectile::OnMissed()
{
	removeFromParent();
}