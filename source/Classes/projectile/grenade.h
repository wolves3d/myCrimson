#ifndef __grenade_h_included__
#define __grenade_h_included__


#include "projectile/projectile.h"


class Grenade : public Projectile
{
public:
	CREATE_FUNC(Grenade);

private:

	void KickUnit(Unit * UnitNode, const CCPoint & BlastDir);
	virtual void OnMissed();
};


#endif // #__grenade_h_included__