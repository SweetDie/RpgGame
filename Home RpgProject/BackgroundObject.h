#pragma once
#include"Object.h"

class BackgroundObject : public Object
{
public:
	BackgroundObject(FloatRect* rect);
	~BackgroundObject();
	virtual void update();

private:
};

