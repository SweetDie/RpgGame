#include "Shop.h"

Shop::Shop()
{
	image.loadFromFile("img/shop2.png");

	texture.loadFromImage(image);

	sprite.setTexture(texture);
	//sprite.setTextureRect(sf::IntRect(0, 0, 125, 145));
	sprite.setPosition(0,35 * 32);
}

void Shop::update()
{
}

void Shop::draw(RenderWindow* window)
{
	int j = 0;
	window->draw(sprite);
	for (auto i : items)
	{
		i.sprite->setPosition(sprite.getPosition().x + j * 32, sprite.getPosition().y);
		window->draw(*i.sprite);
		j++;
	}
}

void Shop::addItem(Item* item)
{
	items.push_back(*item);
}
