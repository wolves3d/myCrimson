#ifndef __player_h_included__
#define __player_h_included__


#include "enemy.h"


class Player : public Unit
{
	// FIXME: visualStudio compiler needs full project rebuild to change this value
	const float m_MoveStep = 5.0f;

public:
	CREATE_FUNC(Player);
	void ShootTo(const CCPoint & target);

private:
	Player();
	virtual bool init();
	virtual void update(float delta);
	virtual float GetRadius() const { return 42; }
	virtual float GetWeight() const { return 1.0f; }

	void HandleKeyboardInput();
	void SetCurrentWeapon(Weapon * weapon);
	Weapon * GetCurrentWeapon()  { return m_Weapon; }
	Weapon * m_Weapon;
};


#endif // #__player_h_included__