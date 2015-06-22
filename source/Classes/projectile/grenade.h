#ifndef __grenade_h_included__
#define __grenade_h_included__


#include "projectile/projectile.h"


class Grenade : public Projectile
{
public:
	CREATE_FUNC(Grenade);

private:
	
	virtual float GetRadius() const { return 67; }
	virtual float GetWeight() const { return 1.0f; }

	void KickUnit(Unit * unit, const CCPoint & blastDir);
	virtual void OnMissed();
};


#endif // #__grenade_h_included__