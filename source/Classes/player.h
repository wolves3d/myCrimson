#ifndef __player_h_included__
#define __player_h_included__


class Player : public CCNode
{
	// FIXME: visualStudio compiler needs full project rebuild to change this value
	const float m_MoveStep = 5.0f;

public:
	CREATE_FUNC(Player);

private:
	Player();
	virtual bool init();
	virtual void update(float delta);

	void HandleKeyboardInput();
	void Fire();
};


#endif // #__player_h_included__