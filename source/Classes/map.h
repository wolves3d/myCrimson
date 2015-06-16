#ifndef __map_h_included__
#define __map_h_included__


class Map : public CCLayer
{
public:
	Map();
	CREATE_FUNC(Map);
	void MapInit(Player * player);

	/// Handle map scroll
	void OnPlayerMoved(); 

private:
	virtual bool init();

	Player * m_pPlayer;
	CCPoint m_ZeroPoint;
};


#endif // #ifndef __map_h_included__