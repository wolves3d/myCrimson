#ifndef __map_h_included__
#define __map_h_included__


class Map : public CCLayer
{
public:
	CREATE_FUNC(Map);
	void MapInit(Player * player);

	/// Handle map scroll
	void OnPlayerMoved(); 
	void ShootGround(const CCPoint * windowCoord);

private:
	Map();
	virtual bool init();
	
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	void ShootGround(CCTouch * touch);

	Player * m_pPlayer;
	CCPoint m_ZeroPoint;
	CCPoint m_LastShootPoint;
};


#endif // #ifndef __map_h_included__