#ifndef __weapon_h_included__
#define __weapon_h_included__


class Weapon : public CCNode
{
public:
	CREATE_FUNC(Weapon);
	bool Fire(const CCPoint & origin, const CCPoint & target);

private:
	Weapon();
	bool IsCooldown() const;
	virtual uint GetCooldownTime() const { return 300; }
	virtual float GetProjectileSpeed() const { return 650.0f;  } // points per second

	uint m_LastShotTime;
};


#endif // #__weapon_h_included__