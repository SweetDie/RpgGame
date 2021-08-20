#include "Gold.h"

Gold::Gold(FloatRect* rect)
{
    this->name = "Gold";
    this->durability = RESOURCE_DURABILITY_GOLD;
    this->alive = true;
    damageToLoot2 = new Atribute<int>(RESOURCE_DAMAGE_TO_LOOT_GOLD, RESOURCE_DAMAGE_TO_LOOT_GOLD);

    this->rect = *rect;
    this->position.x = rect->left;
    this->position.y = rect->top;
    intRect.left = static_cast<int>(rect->left);
    intRect.top = static_cast<int>(rect->top);
    intRect.width = static_cast<int>(rect->width);
    intRect.height = static_cast<int>(rect->height);
}

Gold::Gold(FloatRect* rect, int gid) : Gold(rect)
{
    this->gid = gid;
}

void Gold::update()
{
}
