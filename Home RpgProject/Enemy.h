#pragma once
#include"Unit.h"

class Enemy : public Unit
{
public:
	Enemy(Unit* hero = nullptr);
	Enemy(Atribute<float>* healthPoints, Atribute<float>* manaPoints, Atribute<float>* moveSpeed, Atribute<float>* damage, Atribute<float>* armor, Unit* hero = nullptr);
	Enemy(float healthPoints, float manaPoints, float moveSpeed, float damage, float armor, Unit* hero = nullptr);
	~Enemy();

	const RectangleShape* getBox() const;
	void setPosition(Vector2f position) override;
	void setPosition(float x, float y) override;
	void setPosition(int tileX, int tileY) override;
	Text* getText() const;

	void loadImage() override;
	void update() override;
protected:
	Font font;
	Text* health;
};

