#pragma once
#include"Atribute.h"

class Skill
{
public:
	Skill(string name, float manaCost, float damage, float cooldown);
	// gets
	string getName() const;
	float getManaCost() const;
	float getDamage() const;
	float getCooldown() const;
	int getLevel() const;

	void setLevelFactor(float manacostFactor, float damageFactor, float cooldownFactor);
	void levelUp();
private:
	string name;
	float manaCost;
	float damage;
	float cooldown;
	float manacostFactor;
	float damageFactor;
	float cooldownFactor;
	int level;

	Image* image;
	Texture* texture;
	Sprite* sprite;
};

