#pragma once
#include"Hero.h"

class MyText
{
public:
	MyText(View* view);
	MyText(Hero* hero, View* view);
	MyText(Vector2f position, Hero* hero, View* view);

	void setPosition(Vector2f position);
	void setPosition(float x, float y);

	void draw(RenderWindow* window);
private:
	void update();
	Vector2f* position;
	Text* resourceDiamonds;
	Text* resourceGolds;
	Text* resourceWoods;
	Text* healthPoints;
	Text* manaPoints;
	Hero* hero;
	Font font;
	View* view;
};

