#include "pch.h"
#include "game_logic.h"
#include "player.h"
#include "map.h"
#include "enemy.h"
#include "projectile/projectile.h"


GameLogic * g_GameLogic = NULL;


GameLogic::GameLogic()
: m_EnemyArray(NULL)
{
	g_GameLogic = this;
}


bool GameLogic::init()
{
	if (false == CCNode::init())
		return false;

	m_EnemyArray = CCArray::create();
	m_EnemyArray->retain();

	Map * mapLayer = Map::create();
	if (NULL != mapLayer)
	{
		const CCSize mapSize(g_Map->getContentSize());
		m_UniformGrid.InitGridMap(ccpFromSize(mapSize), 64);

		const CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		const CCPoint halfScreen(0.5f * winSize.width, 0.5f * winSize.height);
		mapLayer->setPosition(halfScreen);
		addChild(mapLayer, -1); // negative z-order to make visible gamelogic debug draws

		Player * playerNode = Player::create();
		if (NULL != playerNode)
		{
			mapLayer->MapInit(playerNode);
			OnAddUnit(playerNode);
		}
	}

	CreateEnemies();
	scheduleUpdate();

	return true;
}


void GameLogic::free()
{
	// FIXME: memory leak, GameLogic::free() never called

	CC_SAFE_RELEASE_NULL(m_EnemyArray);
}


void GameLogic::CreateEnemies()
{
	const uint enemyCount = 2000;
	const CCSize mapSize = g_Map->getContentSize();
	srand(TimeInMilliseconds());

	m_UnitListForCallbacks.reserve(enemyCount);

	for (uint i = 0; i < enemyCount; ++i)
	{
		Enemy * enemy = Enemy::create("enemy.png");
		enemy->setPositionX(RND_INTERVAL(-0.5f, 0.5f) * (mapSize.width * 0.9f));
		enemy->setPositionY(RND_INTERVAL(-0.5f, 0.5f) * (mapSize.height * 0.9f));
		
		OnAddUnit(enemy);

		enemy->StartAI();
	}

	// -------------

	const uint rockCount = 20;

	for (uint i = 0; i < rockCount; ++i)
	{
		Enemy * rock = Enemy::create("rock.png");
		rock->setPositionX(RND_INTERVAL(-0.5f, 0.5f) * (mapSize.width * 0.9f));
		rock->setPositionY(RND_INTERVAL(-0.5f, 0.5f) * (mapSize.height * 0.9f));

		rock->SetWeight(1.0f);
		rock->SetRadius(45);
		OnAddUnit(rock);
	}
}

void GameLogic::OnAddUnit(Unit * unit)
{
	g_Map->addChild(unit);
	m_EnemyArray->addObject(unit);

	m_UniformGrid.AddUnit(unit);
}


void GameLogic::OnRemoveUnit(Unit * UnitNode, bool LeaveBodyFlag)
{
	m_EnemyArray->removeObject(UnitNode);
	m_UniformGrid.RemoveUnit(UnitNode);

	if (false == LeaveBodyFlag)
	{
		g_Map->removeChild(UnitNode);
	}
}


void GameLogic::draw()
{
	CCNode::draw();
	//m_QuadTree->DebugDraw(g_Map);
}


void GameLogic::update(float delta)
{
	CCNode::update(delta);

	{
		m_UniformGrid.Collide(&m_UnitListForCallbacks, this);
	}

	//CCLog("collision test (%d) collisions detected %d", a, b);

	uint c = m_EnemyArray->count();
	while (c--)
	{
		Enemy * enemy = (Enemy *)m_EnemyArray->objectAtIndex(c);
		OnEnemyMoved(enemy);
	}
	
}


void GameLogic::ProcessColliders(UnitVector * targetVector)
{
	const uint unitCount = targetVector->size();


	for (uint i = 0; i < unitCount; ++i)
	{
		Unit * unitA = targetVector->at(i);

		for (uint j = (i+1); j < unitCount; ++j)
		{
			Unit * unitB = targetVector->at(j);

			const CCPoint posA(unitA->getPosition());
			const CCPoint posB(unitB->getPosition());

			const float radiusSum = unitA->GetRadius() + unitB->GetRadius();
			const float minDistanceSq = (radiusSum * radiusSum);
			const float actualDistance = posA.getDistanceSq(posB);

			if (actualDistance < minDistanceSq)
			{
				// collision detected

				const float penetrationDepth = -(ccpDistance(posA, posB) - radiusSum);
				const CCPoint pushVector = ccpMult(ccpSub(posB, posA).normalize(), 0.1f * penetrationDepth);// .normalize(), 0.1f * penetrationDepth);

				// pull objects
				unitA->setPosition(ccpSub(posA, ccpMult(pushVector, (1.0f - unitA->GetWeight()))));
				unitB->setPosition(ccpAdd(posB, ccpMult(pushVector, (1.0f - unitB->GetWeight()))));
			}
		}
	}
}


void GameLogic::OnEnemyHit(Enemy * enemy, Projectile * projectile)
{
	m_EnemyArray->removeObject(enemy);
	enemy->removeFromParent();
}


void GameLogic::OnEnemyMoved(Enemy * enemy)
{
	CCPoint halfMap = ccpMult(ccpFromSize(g_Map->getContentSize()), 0.45f);
	CCPoint pos = enemy->getPosition();

	if (pos.x < (-halfMap.x))
	{
		pos.x = -halfMap.x;
	}
	else if (pos.x > halfMap.x)
	{
		pos.x = halfMap.x;
	}

	if (pos.y < (-halfMap.y))
	{
		pos.y = -halfMap.y;
	}
	else if (pos.y > halfMap.y)
	{
		pos.y = halfMap.y;
	}
	
	enemy->setPosition(pos);
	m_UniformGrid.AddUnit(enemy); // will work fine
}


UnitVector * GameLogic::GetUnitsInRadius(const CCPoint & point, float radius)
{
	// FIXME: WARNING: will break collider - same vector used!
	// FIXME: WARNING: do not call while in collide iteration!

	m_UniformGrid.GetUnitsInRadius(&m_UnitListForCallbacks, point, radius);
	return &m_UnitListForCallbacks;
}