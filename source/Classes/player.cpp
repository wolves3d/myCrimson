#include "pch.h"
#include "player.h"


Player::Player()
{

}


bool Player::init()
{
	if (false == CCNode::init())
		return false;

	CCSprite* pSprite = CCSprite::create("hero.png");

	if (NULL == pSprite)
	{
		return false;
	}

	addChild(pSprite);
	scheduleUpdate();
	return true;
}


void Player::update(float delta)
{
	HandleKeyboardInput();
}


void Player::HandleKeyboardInput()
{
	if (0x80 & GetKeyState('W'))
	{
		CCPoint prevPos = getPosition();
		prevPos.y += 10;
		setPosition(prevPos);
	}
	else if (0x80 & GetKeyState('S'))
	{
		CCPoint prevPos = getPosition();
		prevPos.y -= 10;
		setPosition(prevPos);
	}

	if (0x80 & GetKeyState('A'))
	{
		CCPoint prevPos = getPosition();
		prevPos.x -= 10;
		setPosition(prevPos);
	}
	else if (0x80 & GetKeyState('D'))
	{
		CCPoint prevPos = getPosition();
		prevPos.x += 10;
		setPosition(prevPos);
	}
}