#include "Unit.h"

Unit::~Unit()
{
}

const Atribute<float>& Unit::getHealthPoints() const
{
    return *healthPoints;
}

const Atribute<float>& Unit::getManaPoints() const
{
    return *manaPoints;
}

const Atribute<float>& Unit::getMoveSpeed() const
{
    return *moveSpeed;
}

const Atribute<float>& Unit::getDamage() const
{
    return *damage;
}

const Atribute<float>& Unit::getArmor() const
{
    return *armor;
}

int Unit::getLevel() const
{
    return level;
}

Sprite* Unit::getSprite() const
{
    return sprite;
}

void Unit::setHealthPoints(Atribute<float>* atribute)
{
    healthPoints = atribute;
}

void Unit::setManaPoints(Atribute<float>* atribute)
{
    manaPoints = atribute;
}

int Unit::attack(Unit* enemy)
{
    if (!enemy->takeDamage(this->damage->getCurrent()))
    {
        return HERO_KILL;
    }
    else if (!takeDamage(enemy->getDamage().getCurrent()))
    {
        return HERO_DIE;
    }
    else
    {
        return 0;
    }
}

int Unit::attack(Unit* enemy, Skill* skill)
{
    if (!enemy->takeDamage(skill))
    {
        return HERO_KILL;
    }
    else if (!takeDamage(enemy->getDamage().getCurrent()))
    {
        return HERO_DIE;
    }
    else
    {
        return 0;
    }
}

Skill* Unit::conjure(int skillNumber)
{
    if (skillNumber > skills.size() || skillNumber <= 0)
    {
    	throw exception("uncorrect skill number");
    }
    if (this->manaPoints->getCurrent() < skills[skillNumber - 1].getManaCost())
    {
        return nullptr;
    }
    *this->manaPoints -= skills[skillNumber - 1].getManaCost();
    return &skills[skillNumber - 1];
}

bool Unit::takeDamage(float damage)
{
    damage -= this->armor->getCurrent() * ARMOR_FACTOR;
    *this->healthPoints -= damage;
    if (this->healthPoints->getCurrent() == 0)
    {
    	this->alive = false;
    }
    else
    	this->alive = true;
    update();
    return this->alive;
}

bool Unit::takeDamage(Skill* skill)
{
    *this->healthPoints -= skill->getDamage();
    if (this->healthPoints->getCurrent() == 0)
    {
    	this->alive = false;
    }
    else
    	this->alive = true;
    update();
    return this->alive;
}
