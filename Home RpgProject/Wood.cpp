#include "Wood.h"

Wood::Wood(FloatRect* rect)
{
        this->name = "Wood";
        this->durability = RESOURCE_DURABILITY_WOOD;
        this->alive = true;
        damageToLoot2 = new Atribute<int>(RESOURCE_DAMAGE_TO_LOOT_WOOD, RESOURCE_DAMAGE_TO_LOOT_WOOD);

		this->rect = *rect;
		this->position.x = rect->left;
		this->position.y = rect->top;
		intRect.left = static_cast<int>(rect->left);
		intRect.top = static_cast<int>(rect->top);
		intRect.width = static_cast<int>(rect->width);
		intRect.height = static_cast<int>(rect->height);
}

Wood::Wood(FloatRect* rect, int gid) : Wood(rect)
{
	this->gid = gid;
}

void Wood::update()
{
}
