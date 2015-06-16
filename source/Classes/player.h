#ifndef __player_h_included__
#define __player_h_included__

class Player : public CCNode
{
public:
	Player();
	CREATE_FUNC(Player);

private:
	virtual bool init();
	virtual void update(float delta);

	void HandleKeyboardInput();
};

#endif // #__player_h_included__