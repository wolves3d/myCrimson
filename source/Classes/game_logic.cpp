#include "pch.h"
#include "game_logic.h"
#include "player.h"
#include "map.h"
#include "enemy.h"
#include "projectile.h"
#include "quad_tree.h"


GameLogic * g_GameLogic = NULL;


GameLogic::GameLogic()
	: m_ProjectileArray(NULL)
	, m_QuadTree(NULL)
{
	g_GameLogic = this;
}


bool GameLogic::init()
{
	if (false == CCNode::init())
		return false;

	m_ProjectileArray = CCArray::create();
	m_ProjectileArray->retain();

	m_EnemyArray = CCArray::create();
	m_EnemyArray->retain();

	Map * mapLayer = Map::create();
	if (NULL != mapLayer)
	{
		const CCSize mapSize(g_Map->getContentSize());
		m_QuadTree = new QuadTree(mapSize.width, mapSize.height, 256);

		const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		const CCPoint halfScreen(0.5f * winSize.width, 0.5f * winSize.height);
		mapLayer->setPosition(halfScreen);
		addChild(mapLayer, -1); // negative z-order to make visible gamelogic debug draws

		Player * playerNode = Player::create();
		if (NULL != playerNode)
		{
			mapLayer->MapInit(playerNode);
		}
	}

	CreateEnemies();
	scheduleUpdate();

	return true;
}


void GameLogic::free()
{
	// FIXME: memory leak, never called

	CC_SAFE_DELETE(m_QuadTree);
	m_QuadTree = NULL;

	CC_SAFE_RELEASE_NULL(m_EnemyArray);
	CC_SAFE_RELEASE_NULL(m_ProjectileArray);
}


void GameLogic::CreateEnemies()
{
	const CCSize mapSize = g_Map->getContentSize();
	srand(TimeInMilliseconds());

	for (uint i = 0; i < 100; ++i)
	{
		Enemy * enemy = Enemy::create();
		enemy->setPositionX((((float)rand() / 32768.f) - 0.5f) * mapSize.width);
		enemy->setPositionY((((float)rand() / 32768.f) - 0.5f) * mapSize.height);
		g_Map->addChild(enemy);

		m_EnemyArray->addObject(enemy);
		enemy->StartAI();
	}
}


void GameLogic::OnProjectileCreated(Projectile * projectile)
{
	m_ProjectileArray->addObject(projectile);
}


void GameLogic::OnProjectileDeleted(Projectile * projectile)
{
	m_ProjectileArray->removeObject(projectile);
}


void GameLogic::draw()
{
	CCNode::draw();
	m_QuadTree->DebugDraw(g_Map);
}


void GameLogic::update(float delta)
{
	CCNode::update(delta);

	// FIXME: non optimal, refactor me
	CCObject * projectileObj;
	CCARRAY_FOREACH(m_ProjectileArray, projectileObj)
	{
		Projectile * projectile = (Projectile *)projectileObj;

		// FIXME: non optimal, refactor me
		uint c = m_EnemyArray->count();
		while (c--)
		{
			Enemy * enemy = (Enemy *)m_EnemyArray->objectAtIndex(c);
			if (true == enemy->HitTest(projectile))
			{
				// FIXME: One bullet - one hit?
				//break;
			}
		}
	}
}


void GameLogic::OnEnemyHit(Enemy * enemy, Projectile * projectile)
{
	m_EnemyArray->removeObject(enemy);
	enemy->removeFromParent();
}