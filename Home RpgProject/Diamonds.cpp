#include "Diamonds.h"

Diamonds::Diamonds(FloatRect* rect)
{
    this->name = "Diamonds";
    this->durability = RESOURCE_DURABILITY_DIAMONDS;
    this->alive = true;
    damageToLoot2 = new Atribute<int>(RESOURCE_DAMAGE_TO_LOOT_DIAMONDS, RESOURCE_DAMAGE_TO_LOOT_DIAMONDS);

	this->rect = *rect;
	this->position.x = rect->left;
	this->position.y = rect->top;
	intRect.left = static_cast<int>(rect->left);
	intRect.top = static_cast<int>(rect->top);
	intRect.width = static_cast<int>(rect->width);
	intRect.height = static_cast<int>(rect->height);
}

Diamonds::Diamonds(FloatRect* rect, int gid) : Diamonds(rect)
{
	this->gid = gid;
}

void Diamonds::update()
{
}
