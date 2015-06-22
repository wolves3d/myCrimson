#ifndef __projectile_h_included__
#define __projectile_h_included__


#include "Enemy.h"


class Projectile : public Enemy
{
public:
	CREATE_FUNC(Projectile);
	void Go(CCPoint target, float speed, float maxDistance);

protected:
	virtual bool init();
	virtual void OnMissed();

private:
	virtual float GetRadius() const { return 67; }
	virtual float GetWeight() const { return 1.0f; }
};


#endif // #__projectile_h_included__