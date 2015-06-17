#include "pch.h"
#include "player.h"
#include "map.h"
#include "projectile.h"


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

	// FIXME: WIN32 specific, no multiplatform keyboard support

	// Vertical moving
	if ((0x80 & GetKeyState('W')) || (0x80 & GetKeyState(VK_UP)))
	{
		playerOffset.y += m_MoveStep;
	}
	else if ((0x80 & GetKeyState('S')) || (0x80 & GetKeyState(VK_DOWN)))
	{
		playerOffset.y -= m_MoveStep;
	}

	// Horizontal moving
	if ((0x80 & GetKeyState('A')) || (0x80 & GetKeyState(VK_LEFT)))
	{
		playerOffset.x -= m_MoveStep;
	}
	else if ((0x80 & GetKeyState('D')) || (0x80 & GetKeyState(VK_RIGHT)))
	{
		playerOffset.x += m_MoveStep;
	}

	// Fire
	if ((0x80 & GetKeyState(VK_LBUTTON)) || (0x80 & GetKeyState(VK_RCONTROL)))
	{
		Fire();
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


void Player::Fire()
{
	// FIXME: add cooldown test here

	CCPoint shootDirection(0, 0);

	// Get direction
	Projectile * bullet = Projectile::create();
	if (NULL != bullet)
	{
		g_Map->addChild(bullet);
		bullet->setPosition(getPosition());
		bullet->Go(shootDirection);
	}	
}