#ifndef __game_logic_h_included__
#define __game_logic_h_included__


class GameLogic : public CCNode
{
public:
	CREATE_FUNC(GameLogic);
	void free();
	void OnProjectileCreated(Projectile * projectile);
	void OnProjectileDeleted(Projectile * projectile);
	void OnEnemyHit(Enemy * enemy, Projectile * projectile);

private:
	GameLogic();
	virtual bool init();
	virtual void draw();
	virtual void update(float delta);

	void CreateEnemies();

	CCArray * m_ProjectileArray;
	CCArray * m_EnemyArray;
	QuadTree * m_QuadTree;
};


#endif // #__game_logic_h_included__