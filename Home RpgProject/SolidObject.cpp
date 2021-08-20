#include "SolidObject.h"

SolidObject::SolidObject(FloatRect* rect)
{
	/*
	this->rect = new FloatRect(*rect);
	position = new Vector2f(rect->left, rect->top);
	intRect = new IntRect(static_cast<int>(rect->left), static_cast<int>(rect->top), static_cast<int>(rect->width), static_cast<int>(rect->height));
	*/
	this->alive = true;
	this->rect = *rect;
	this->position.x = rect->left;
	this->position.y = rect->top;
	intRect.left = static_cast<int>(rect->left);
	intRect.top = static_cast<int>(rect->top);
	intRect.width = static_cast<int>(rect->width);
	intRect.height = static_cast<int>(rect->height);
}

SolidObject::~SolidObject()
{
	
}

void SolidObject::update()
{
}
