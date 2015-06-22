#include "pch.h"
#include "game_logic.h"
#include "map.h"
#include "projectile/grenade.h"


void Grenade::KickUnit(Unit * unit, const CCPoint & blastDir)
{
	/*
	unit->setPosition(ccpAdd(unit->getPosition(), blastDir));

	CCPoint targetDir = ccpSub(target, getPosition());
	const float shootDistance = targetDir.getLength();

	// Set start projectile rotation
	targetDir = targetDir.normalize();
	const float angle = -atan2f(targetDir.y, targetDir.x);
	setRotation(RADIAN_TO_DEGREE(angle));

	const float flyTime = (shootDistance / speed);

	// Override target
	target = ccpAdd(getPosition(), ccpMult(targetDir, maxDistance));
	*/



	CCPoint unitOffset = ccpMult(blastDir, RND_INTERVAL(0.75f, 1.5f));

	const float flyTime = 0.4f;

	unit->runAction(
		CCEaseSineOut::create(CCMoveTo::create(flyTime, ccpAdd(unit->getPosition(), unitOffset))));

	//unit->runAction(CCRotateBy::create(flyTime, (RND_FLOAT > 0.5f) ? 360 : (-360)));
	unit->runAction(CCRotateBy::create(flyTime, 90 + RND_INTERVAL(-180, 180)));


	unit->runAction(
		CCEaseSineOut::create(
		CCSequence::createWithTwoActions(
		CCScaleTo::create(0.5f * flyTime, 1.25f),
		CCScaleTo::create(0.5f * flyTime, 1))));
}


void Grenade::OnMissed()
{
	const float explosionRadius = 90;
	const float explosionRadiusSq = (explosionRadius * explosionRadius);
	const CCPoint explosionCenter(getPosition());

	UnitVector * unitList = g_GameLogic->GetUnitsInRadius(explosionCenter, explosionRadius);

	uint i = unitList->size();
	while (i--)
	{
		Unit * unit = unitList->at(i);
		const CCPoint unitPos(unit->getPosition());

		if (explosionRadiusSq > explosionCenter.getDistanceSq(unitPos))
		{
			CCPoint blastDir(ccpSub(unitPos, explosionCenter).normalize());

			// FIXME: do better!
			blastDir = ccpMult(blastDir, explosionRadius);

			KickUnit(unit, blastDir);
		}
	}




	// =========================================================================

	int loopCount = 1;
	//string animName = "resources/ipadhd/explosion.plist";
	string animName = "ma-eff-mutation";

	CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile((animName + ".plist").c_str());

	char buff[1024];

	CCAnimation * result = NULL;
	CCArray * frameArray = NULL;

	for (uint i = 0; (true); ++i)
	{
		sprintf(buff, "%s_%02d.png", animName.c_str(), i);
		CCSpriteFrame * frame = frameCache->spriteFrameByName(buff);

		if (NULL == frame)
			break;

		if (NULL == frameArray)
			frameArray = CCArray::create();

		frameArray->addObject(frame);
	}

	if (NULL != frameArray)
	{
		const float frameDelay = 1.0f / 30;
		result = CCAnimation::createWithSpriteFrames(frameArray, frameDelay);

		// 		if (NULL != result)
		// 			result->retain();

		CCAnimate* animate = CCAnimate::create(result);

		CCAction * action;
		if (loopCount >= 0)
		//if (false)
		{
			CCArray * actionList = CCArray::create();

			actionList->addObject(
				CCRepeat::create(animate, loopCount));

			actionList->addObject(
				CCRemoveSelf::create());

			/*
			if (NULL != callBack)
			{
			actionList->addObject(callBack);
			}

			actionList->addObject(
			CCCallFunc::create(sprite, callfunc_selector(CCSpriteEx::OnAnimationEnded)));
			*/
			action = CCSequence::create(actionList);
		}
		else
		{
			action = CCRepeatForever::create(animate);
		}


		CCSprite * explosionEffectNode = CCSprite::create();
		g_Map->addChild(explosionEffectNode);
		explosionEffectNode->setPosition(getPosition());

		explosionEffectNode->runAction(action);
	}



	Projectile::OnMissed();
}