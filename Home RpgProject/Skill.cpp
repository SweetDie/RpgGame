#include "Skill.h"

Skill::Skill(string name, float manaCost, float damage, float cooldown) : name{ name }, manaCost{ manaCost }, damage{ damage }, cooldown{ cooldown }
{
	this->damageFactor = SKILL_LEVEL_FACTOR;
	this->manacostFactor = SKILL_LEVEL_FACTOR;
	this->cooldown = SKILL_LEVEL_COOLDOWN_FACTOR;
}

string Skill::getName() const
{
	return name;
}

float Skill::getManaCost() const
{
	return manaCost;
}

float Skill::getDamage() const
{
	return damage;
}

float Skill::getCooldown() const
{
	return cooldown;
}

int Skill::getLevel() const
{
	return level;
}

void Skill::setLevelFactor(float manacostFactor, float damageFactor, float cooldownFactor)
{
	if (manacostFactor >= 1 & damageFactor >= 1)
	{
		this->manacostFactor = manacostFactor;
		this->damageFactor = damageFactor;
	}
	if (cooldown >= 0)
	{
		this->cooldownFactor = cooldownFactor;
	}
}

void Skill::levelUp()
{
	this->damage *= this->damageFactor;
	this->manaCost *= this->manacostFactor;
	this->cooldown -= this->cooldownFactor;
}
