#include "BackgroundObject.h"

BackgroundObject::BackgroundObject(FloatRect* rect)
{
	this->alive = true;
	this->rect = *rect;
	this->position.x = rect->left;
	this->position.y = rect->top;
	intRect.left = static_cast<int>(rect->left);
	intRect.top = static_cast<int>(rect->top);
	intRect.width = static_cast<int>(rect->width);
	intRect.height = static_cast<int>(rect->height);
}

BackgroundObject::~BackgroundObject()
{
	
}

void BackgroundObject::update()
{
}
