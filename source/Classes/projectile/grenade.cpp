#include "pch.h"
#include "game_logic.h"
#include "map.h"
#include "projectile/grenade.h"
#include "animation.h"
#include "player.h"


void Grenade::KickUnit(Unit * UnitNode, const CCPoint & BlastDir)
{
	UnitNode->stopAllActions();
	g_GameLogic->OnRemoveUnit(UnitNode, true);

	const float flyTime = 0.4f + RND_INTERVAL(-0.2f, +0.2f);
	const CCPoint UnitOffset = ccpMult(BlastDir, RND_INTERVAL(0.75f, 1.5f));

	UnitNode->runAction(CCSequence::createWithTwoActions(
		CCMoveTo::create(flyTime, ccpAdd(UnitNode->getPosition(), UnitOffset)),
		CCCallFunc::create(UnitNode, callfunc_selector(Enemy::OnDie))));


	// rotate while flying
	UnitNode->runAction(CCRotateBy::create(flyTime, 90 + RND_INTERVAL(-180, 180)));

	// scale while flying
	UnitNode->runAction(
		CCEaseSineOut::create(
		CCSequence::createWithTwoActions(
		CCScaleTo::create(0.5f * flyTime, 1.25f),
		CCScaleTo::create(0.5f * flyTime, 1))));
}


void Grenade::OnMissed()
{
	const float explosionRadius = 90;
	const float explosionRadiusSq = (explosionRadius * explosionRadius);
	const CCPoint explosionCenter(getPosition());

	Unit * GrenadeNode = this;
	Unit * PlayerNode = g_Player;
	UnitVector * unitList = g_GameLogic->GetUnitsInRadius(explosionCenter, explosionRadius);

	uint i = unitList->size();
	while (i--)
	{
		Unit * unit = unitList->at(i);

		if ((GrenadeNode == unit) || (PlayerNode == unit))
		{
			// Do not affect projectile itself and player
			continue;
		}

		const CCPoint unitPos(unit->getPosition());

		if (explosionRadiusSq > explosionCenter.getDistanceSq(unitPos))
		{
			CCPoint blastDir(ccpSub(unitPos, explosionCenter).normalize());

			// FIXME: do better!
			blastDir = ccpMult(blastDir, explosionRadius);

			KickUnit(unit, blastDir);
		}
	}


	Animation * ExplosionVFX = Animation::create();
	ExplosionVFX->Play("ma-eff-mutation", NULL, 30);

	g_Map->addChild(ExplosionVFX);
	ExplosionVFX->setPosition(getPosition());

	Projectile::OnMissed();
}