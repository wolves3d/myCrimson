#ifndef __wandering_task_h_included__
#define __wandering_task_h_included__


#include "base_ai.h"
#include "enemy.h"


class WanderingTask : public BaseAI
{
public:
	CREATE_FUNC(WanderingTask);

private:

	virtual void update(float delta);

	virtual void OnBegin();
	virtual void OnSubTaskEnded(BaseAI * subTask);

	void GoSomewhere();
};


#endif // #__wandering_task_h_included__