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


void Projectile::Go(const CCPoint & target, float speed)
{
	CCPoint targetDir = ccpSub(target, getPosition());
	const float shootDistance = targetDir.getLength();

	// Set start projectile rotation
	targetDir.normalize();
	const float angle = -atan2f(targetDir.y, targetDir.x);
	setRotation(RADIAN_TO_DEGREE(angle));	

	const float flyTime = (shootDistance / speed);

	CCAction * action = CCSequence::createWithTwoActions(
		CCMoveTo::create(flyTime, target),
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