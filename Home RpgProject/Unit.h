#pragma once
#include"Skill.h"
#include"Object.h"
#include"Map.h"

class Unit : public Object
{
public:
	enum Direction
	{
		Up,
		Down,
		Right,
		Left
	};

	virtual ~Unit();
	// gets
	virtual const Atribute<float>& getHealthPoints() const;
	virtual const Atribute<float>& getManaPoints() const;
	virtual const Atribute<float>& getMoveSpeed() const;
	virtual const Atribute<float>& getDamage() const;
	virtual const Atribute<float>& getArmor() const;
	virtual int getLevel() const;
	Sprite* getSprite() const;
	virtual const RectangleShape* getBox() const = 0;

	virtual void setHealthPoints(Atribute<float>* atribute);
	virtual void setManaPoints(Atribute<float>* atribute);

	virtual int attack(Unit* enemy);
	virtual int attack(Unit* enemy, Skill* skill);
	virtual Skill* conjure(int skillNumber);
	virtual bool takeDamage(float damage);
	virtual bool takeDamage(Skill* skill);
	virtual void loadImage() = 0;

protected:
	Atribute<float>* healthPoints;
	Atribute<float>* manaPoints;
	Atribute<float>* moveSpeed;
	Atribute<float>* damage;
	Atribute<float>* armor;
	vector<Skill> skills;
	int level;

	Image* image;
	Texture* texture;
	Sprite* sprite;
};

