#pragma once
#include"Enemy.h"

class Hero : public Unit
{
public:
	Hero(Atribute<float>* healthPoints, Atribute<float>* manaPoints, Atribute<float>* moveSpeed, Atribute<float>* damage, Atribute<float>* armor);
	Hero(float healthPoints, float manaPoints, float moveSpeed, float damage, float armor);
	~Hero();

	const RectangleShape* getBox() const override;

	bool addSkill(Skill skill);
	void levelUp();
	void loadAnimation();
	void loadImage() override;
	void move(Clock* clock, Direction rotation, Map* map);
	void update() override;
	void action(Map* map, RenderWindow* window, vector<Enemy*>* enemies);

	int* getGold();
	int* getWood();
	int* getDiamond();

	void setLevelFactor(double healthPointsFactor, double manaPointsFactor, float moveSpeedFactor, double damageFactor, double armorFactor);
private:
	Atribute<int>* mineDamage;
	Atribute<float>* experience;
	RectangleShape* unitBox;

	float healthPointsFactor;
	float manaPointsFactor;
	float moveSpeedFactor;
	float damageFactor;
	float armorFactor;

	int goldNumber;
	int diamondNumber;
	int woodNumber;

public:
	vector<vector<IntRect>> animationList{ Animation::Size };
	Text textDiamonds;
	Text text;
	enum Animation
	{
		MoveUp,
		MoveDown,
		MoveRight,
		MoveLeft,
		Run,
		Attack,
		Die,
		Size
	};
	friend class MyText;
};

