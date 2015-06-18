#ifndef __projectile_h_included__
#define __projectile_h_included__


class Projectile : public CCNode
{
public:
	CREATE_FUNC(Projectile);
	void Go(CCPoint target, float speed, float maxDistance);

private:
	virtual bool init();

	virtual void OnMissed();
};


#endif // #__projectile_h_included__