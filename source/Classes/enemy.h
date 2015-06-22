#ifndef __enemy_h_included__
#define __enemy_h_included__


class Enemy
	: public CCNode
{
public:
	static Enemy * create(const char * SpriteName);
	bool HitTest(Projectile * projectile);
	void StartAI();

	void SetRadius(float Radius) { m_Radius = Radius; }
	float GetRadius() const { return m_Radius;  }

	void SetWeight(float Weight) { m_Weight = Weight; }
	float GetWeight() const { return m_Weight; }

	void OnDie();

	void SetGridIndex(int Idx) { m_GridIndex = Idx; }
	int GetGridIndex() const { return m_GridIndex;  }

protected:
	Enemy();

private:
	void RemoveFromMap();
	//virtual bool init();

	float m_Weight;
	float m_Radius;
	int m_GridIndex;
};


#endif // #__enemy_h_included__