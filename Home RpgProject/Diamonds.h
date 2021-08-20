#pragma once
#include"Resources.h"

class Diamonds : public Resources
{
public:
	Diamonds(FloatRect* rect);
	Diamonds(FloatRect* rect, int gid);
	virtual void update();
};

