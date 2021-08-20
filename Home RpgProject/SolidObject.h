#pragma once
#include"Object.h"

class SolidObject : public Object
{
public:
	SolidObject(FloatRect* rect);
	~SolidObject();
	virtual void update();
private:
};

