#pragma once
#include"Constants.h"
#include"Defines.h"

class Object
{
public:
	virtual ~Object();
	virtual bool getAlive() const;
	virtual FloatRect getRect() const;
	virtual Vector2f getPosition() const;
	virtual IntRect getIntRect() const;
	virtual void update() = 0;
	virtual Sprite* getSprite() const;

	virtual void setPosition(Vector2f position);
	virtual void setPosition(float x, float y);
	virtual void setPosition(int tileX, int tileY);
protected:
	FloatRect rect;
	Vector2f position;
	IntRect intRect;
	bool alive;
};

