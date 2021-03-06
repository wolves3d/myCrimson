#include "pch.h"
#include "map.h"
#include "weapon.h"
#include "projectile/grenade.h"
#include "game_logic.h"


Weapon::Weapon()
	: m_LastShotTime(0)
{
}


bool Weapon::IsCooldown() const
{
	if (0 == m_LastShotTime)
		return false;

	return (TimeInMilliseconds() < (m_LastShotTime + GetCooldownTime()));
}


bool Weapon::Fire(const CCPoint & origin, const CCPoint & target)
{
	if (true == IsCooldown())
		return false;
	
	Projectile * bullet = Grenade::create();
	if (NULL == bullet)
		return false;

	m_LastShotTime = TimeInMilliseconds();
	
	//g_Map->addChild(bullet);
	bullet->setPosition(origin);

	bullet->Go(
		target,
		GetProjectileSpeed(),
		GetShootDistance());

	g_GameLogic->OnAddUnit(bullet);
	
	return true;
}