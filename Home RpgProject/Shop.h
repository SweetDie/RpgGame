#pragma once
#include"Item.h"

class Shop
{
public:
	Shop();
	void update();
	void draw(RenderWindow* window);
	void addItem(Item* item);

	vector<Item> items;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
};

