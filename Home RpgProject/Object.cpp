#include "Object.h"

Object::~Object()
{
}

bool Object::getAlive() const
{
    return alive;
}

FloatRect Object::getRect() const
{
    return rect;
}

Vector2f Object::getPosition() const
{
    return position;
}

IntRect Object::getIntRect() const
{
    return intRect;
}

Sprite* Object::getSprite() const
{
    return nullptr;
}

void Object::setPosition(Vector2f position)
{
}

void Object::setPosition(float x, float y)
{
}

void Object::setPosition(int tileX, int tileY)
{
}
