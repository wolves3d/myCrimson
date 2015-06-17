#ifndef __enemy_h_included__
#define __enemy_h_included__


class Enemy : public CCNode
{
public:
	CREATE_FUNC(Enemy);
	bool HitTest(Projectile * projectile);

private:
	virtual bool init();
};


#endif // #__enemy_h_included__