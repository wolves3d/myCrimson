#include "pch.h"
#include "map.h"
#include "player.h"


Map * g_Map = NULL;


Map::Map()
	: m_pPlayer(NULL)
	, m_ZeroPoint(CCPointZero)
{
	g_Map = this;
}


bool Map::init()
{
	if (false == CCLayer::init())
		return false;

	setTouchEnabled(true);

	CCSprite * mapSprite = CCSprite::create("big_map.jpg");
	if (NULL == mapSprite)
	{
		return false;
	}

	addChild(mapSprite);
	setContentSize(mapSprite->getContentSize());
	return true;
};


void Map::MapInit(Player * player)
{
	m_pPlayer = player;
	m_ZeroPoint = getPosition();
}


void Map::OnPlayerMoved()
{
	const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	const  CCSize mapSize = getContentSize();

	const float widthBorder = ((0.5f * mapSize.width) - (0.5f * winSize.width));
	const float heightBorder = ((0.5f * mapSize.height) - (0.5f * winSize.height));
	const CCPoint playerPos = m_pPlayer->getPosition();

	if (fabsf(playerPos.x) < widthBorder)
	{
		this->setPositionX(m_ZeroPoint.x - playerPos.x);
	}

	if (fabsf(playerPos.y) < heightBorder)
	{
		this->setPositionY(m_ZeroPoint.y - playerPos.y);
	}
}


void Map::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	ShootGround((CCTouch*)(pTouches->anyObject()));
	CCLayer::ccTouchesEnded(pTouches, pEvent);
}


void Map::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	ShootGround((CCTouch*)(pTouches->anyObject()));
	CCLayer::ccTouchesEnded(pTouches, pEvent);
}


void Map::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	ShootGround((CCTouch*)(pTouches->anyObject()));
	CCLayer::ccTouchesEnded(pTouches, pEvent);
}


void Map::ShootGround(CCTouch * touch)
{
	const CCPoint touchLocation = touch->getLocation();
	ShootGround(&touchLocation);
}


void Map::ShootGround(const CCPoint * windowCoord)
{
	if (NULL != windowCoord)
	{
		m_LastShootPoint = (*windowCoord);
	}

	CCPoint target = convertToNodeSpace(m_LastShootPoint);
	m_pPlayer->ShootTo(target);
}