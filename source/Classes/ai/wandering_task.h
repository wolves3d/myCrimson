#ifndef __wandering_task_h_included__
#define __wandering_task_h_included__


#include "base_ai.h"
#include "enemy.h"


class WanderingTask : public BaseAI
{
public:
	CREATE_FUNC(WanderingTask);

private:
	WanderingTask();
	virtual void update(float delta);

	void GoSomewhere();

	virtual void OnBegin();
	virtual void OnSubTaskEnded(BaseAI * subTask);
	virtual void OnFeet();

	bool m_IsFixingRotation;
};


#endif // #__wandering_task_h_included__