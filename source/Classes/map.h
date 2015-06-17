#ifndef __map_h_included__
#define __map_h_included__


class Map : public CCLayer
{
public:
	CREATE_FUNC(Map);
	void MapInit(Player * player);

	/// Handle map scroll
	void OnPlayerMoved(); 

private:
	Map();
	virtual bool init();
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	Player * m_pPlayer;
	CCPoint m_ZeroPoint;
};


#endif // #ifndef __map_h_included__