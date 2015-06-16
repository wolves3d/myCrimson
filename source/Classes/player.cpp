#include "pch.h"
#include "player.h"
#include "map.h"


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
	CCPoint playerOffset = CCPointZero;

	// FIXME: WIN32 specific, no multiplatform support
	if (0x80 & GetKeyState('W'))
	{
		playerOffset.y += m_MoveStep;
	}
	else if (0x80 & GetKeyState('S'))
	{
		playerOffset.y -= m_MoveStep;
	}

	if (0x80 & GetKeyState('A'))
	{
		playerOffset.x -= m_MoveStep;
	}
	else if (0x80 & GetKeyState('D'))
	{
		playerOffset.x += m_MoveStep;
	}

	// early exit?
	if (0 == playerOffset.getLengthSq())
	{
		// no moving at all
		return;
	}

	const CCPoint newPlayerPos = ccpAdd(getPosition(), playerOffset);
	const CCSize mapSize = g_Map->getContentSize();

	// Keep player in map (horizontal border)
	if ((fabsf(newPlayerPos.x) < (0.5f * mapSize.width)))
	{
		setPositionX(newPlayerPos.x);
	}

	// Keep player in map (vertical border)
	if ((fabsf(newPlayerPos.y) < (0.5f * mapSize.height)))
	{
		setPositionY(newPlayerPos.y);
	}

	g_Map->OnPlayerMoved();
}