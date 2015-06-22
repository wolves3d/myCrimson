#ifndef __game_logic_h_included__
#define __game_logic_h_included__


#include "uniform_grid.h"


class GameLogic
	: public CCNode
	, public SortedListDelegate
{
public:
	CREATE_FUNC(GameLogic);
	void free();
	void OnProjectileCreated(Projectile * projectile);
	void OnProjectileDeleted(Projectile * projectile);
	void OnEnemyHit(Enemy * enemy, Projectile * projectile);

	void OnAddUnit(Unit * unit);
	void OnEnemyMoved(Enemy * enemy);

	UnitVector * GetUnitsInRadius(const CCPoint & point, float radius);

private:
	GameLogic();
	virtual bool init();
	virtual void draw();
	virtual void update(float delta);

	void CreateEnemies();

	virtual void ProcessColliders(UnitVector * unitVector);

	CCArray * m_ProjectileArray;
	CCArray * m_EnemyArray;

	UnitVector m_UnitListForCallbacks;
	UniformGrid m_UniformGrid;
};


#endif // #__game_logic_h_included__