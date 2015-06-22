#include "pch.h"
#include "animation.h"


void Animation::Play(const char * AnimName, CCAction * CustomAction, int FrameRate, int LoopCount, bool RemoveOnFinish)
{
	CCSpriteFrameCache * frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();


	char buff[1024]; // FIXME use normal string builder
	sprintf(buff, "%s.plist", AnimName);

	frameCache->addSpriteFramesWithFile(buff);

	// Build frame array 0..N frames

	CCArray * frameArray = NULL;

	for (uint i = 0; (true); ++i)
	{
		sprintf(buff, "%s_%02d.png", AnimName, i);

		CCSpriteFrame * frame = frameCache->spriteFrameByName(buff);

		if (NULL == frame)
			break;

		if (NULL == frameArray)
			frameArray = CCArray::create();

		frameArray->addObject(frame);
	}


	// Build animation

	CCAnimation * Anim = NULL;
	if (NULL != frameArray)
	{
		const float frameDelay = 1.0f / FrameRate;
		Anim = CCAnimation::createWithSpriteFrames(frameArray, frameDelay);
		CCAnimate * Animate = CCAnimate::create(Anim);
		CCAction * Action = NULL;

		if (-1 == LoopCount)
		{
			Action = CCRepeatForever::create(Animate);
		}
		else
		{
			CCArray * ActionList = CCArray::create();
			ActionList->addObject(CCRepeat::create(Animate, MAX(1, LoopCount)));
			
			if (NULL != CustomAction)
			{
				ActionList->addObject(CustomAction);
			}

			if (true == RemoveOnFinish)
			{
				ActionList->addObject(CCRemoveSelf::create());
			}
			
			Action = CCSequence::create(ActionList);
		}


		//CCSprite * explosionEffectNode = CCSprite::create();
		//g_Map->addChild(explosionEffectNode);
		//explosionEffectNode->setPosition(getPosition());

		runAction(Action);
	}
}