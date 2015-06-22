#ifndef __animation_h_included__
#define __animation_h_included__


class Animation : public CCSprite
{
public:
	CREATE_FUNC(Animation);
	void Play(const char * AnimName, CCAction * CustomAction = NULL, int FrameRate = 24, int LoopCount = 1, bool RemoveOnFinish = true);
};


#endif // #__animation_h_included__