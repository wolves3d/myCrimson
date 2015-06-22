#ifndef __enemy_h_included__
#define __enemy_h_included__


class Enemy
	: public CCNode
{
public:
	CREATE_FUNC(Enemy);
	bool HitTest(Projectile * projectile);
	void StartAI();
	virtual float GetRadius() const { return 15;  }
	virtual float GetWeight() const { return 0.1f; }

	void SetGridIndex(int Idx) { m_GridIndex = Idx; }
	int GetGridIndex() const { return m_GridIndex;  }

protected:
	Enemy();

private:
	virtual bool init();

	int m_GridIndex;
};


#endif // #__enemy_h_included__