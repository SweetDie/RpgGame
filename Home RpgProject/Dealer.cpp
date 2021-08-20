#include "Dealer.h"

Dealer::Dealer()
{
	this->alive = true;
	this->level = 0;
	this->healthPoints = nullptr;
	this->manaPoints = nullptr;
	this->moveSpeed = nullptr;
	this->damage = nullptr;
	this->armor = nullptr;

	loadImage();
}

const RectangleShape* Dealer::getBox() const
{
	return nullptr;
}

void Dealer::loadImage()
{
	image = new Image;
	image->loadFromFile(dealerImagePath);

	texture = new Texture;
	texture->loadFromImage(*image);

	sprite = new Sprite;
	sprite->setTexture(*texture);

	position = sprite->getPosition();
	intRect = sprite->getTextureRect();
	rect.left = static_cast<float>(intRect.left);
	rect.top = static_cast<float>(intRect.top);
	rect.width = static_cast<float>(intRect.width);
	rect.height = static_cast<float>(intRect.height);

	sprite->setPosition(5 * 32, 31 * 32 - 16);
}

void Dealer::update()
{

}
