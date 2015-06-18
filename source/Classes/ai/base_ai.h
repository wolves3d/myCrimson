#ifndef __base_ai_h_included__
#define __base_ai_h_included__


#include "enemy.h"


class BaseAI : public CCNode
{
public:
	
	CREATE_FUNC(BaseAI);

	static BaseAI * create(Unit * parentUnit);

	void SetUnit(Unit * unit);
	Unit * GetUnit() { return m_Unit; }
	void AddSubTask(BaseAI * subTask);
	void MoveTo(const CCPoint & target);

protected:
	BaseAI();

private:
	void OnArrived();
	void OnEndReserved();
	

	void SetParentTask(BaseAI * parent);

	virtual void OnBegin() {};
	virtual void OnEnd() {};
	virtual void OnSubTaskEnded(BaseAI * subTask) {};
	
	//virtual bool init();

	BaseAI * m_ParentTask;
	Unit * m_Unit;
};


#endif // #__base_ai_h_included__