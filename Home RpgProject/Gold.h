#pragma once
#include"Resources.h"

class Gold : public Resources
{
public:
	Gold(FloatRect* rect);
	Gold(FloatRect* rect, int gid);
	virtual void update();
};

