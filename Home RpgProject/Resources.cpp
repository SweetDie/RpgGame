#include "Resources.h"

string Resources::getName()
{
    return name;
}

int Resources::getDurability()
{
    return durability;
}

bool Resources::getAlive()
{
    return alive;
}

int Resources::mine(int damage)
{
	int amount = 0;
	while (damage > 0 && durability > 0)
	{
		if (damage >= damageToLoot2->getCurrent())
		{
			if (durability == damageToLoot2->getCurrent() && durability > 0)
			{
				durability = 0;
				alive = false;
				return ++amount;
			}
			else if (durability < damageToLoot2->getCurrent() && durability > 0)
			{
				alive = false;
				durability = 0;
				return amount;
			}
			damage -= damageToLoot2->getCurrent();
			durability -= damageToLoot2->getCurrent();
			damageToLoot2->setCurrent(damageToLoot2->getMax());
			amount++;
			continue;
		}
		else if (damage > 0)
		{
			damageToLoot2->setCurrent(damageToLoot2->getCurrent() - damage);
			durability -= damage;
			damage = 0;
		}
		return amount;
	}
	return amount;
}

int Resources::getGid()
{
	return gid;
}
