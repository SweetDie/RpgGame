#pragma once
#include"Resources.h"

class Wood : public Resources
{
public:
	Wood(FloatRect* rect);
	Wood(FloatRect* rect, int gid);
	virtual void update();
};

