#include "Item.h"

Item::Item(int cost, Atribute<float>* stat, string path, int id)
{
	this->cost = cost;
	this->stat = stat;
	this->description = "";
	this->id = id;

	load(path);
}

Item::Item(int cost, Atribute<float>* stat, string path, string description, int id)
{
	this->cost = cost;
	this->stat = stat;
	this->description = description;
	this->id = id;

	load(path);
}

Item::Item(int cost, float stat, string path, int id)
{
	this->cost = cost;
	this->stat = new Atribute<float>(stat, stat);
	this->description = "";
	this->id = id;

	load(path);
}

Item::Item(int cost, float stat, string path, string description, int id)
{
	this->cost = cost;
	this->stat = new Atribute<float>(stat, stat);
	this->description = description;
	this->id = id;

	load(path);
}

Item::~Item()
{
	//delete stat;
}



void Item::load(string path)
{
	image = new Image;
	image->loadFromFile(path);
	texture = new Texture;
	texture->loadFromImage(*image);
	sprite = new Sprite;
	sprite->setTexture(*texture);
	font.loadFromFile("source/arial.ttf");
	desc = new Text;
	desc->setFont(font);
	desc->setFillColor(Color::Blue);
	desc->setCharacterSize(11);
	desc->setString(description);

	scrollImage = new Image;
	scrollTexture = new Texture;
	scrollSprite = new Sprite;
}

void Item::draw(RenderWindow* window)
{
	scrollImage->loadFromFile("img/scroll.png");
	scrollTexture->loadFromImage(*scrollImage);
	scrollSprite->setTexture(*scrollTexture);
	scrollSprite->setPosition(sprite->getPosition().x, sprite->getPosition().y + 50);
	desc->setPosition(scrollSprite->getPosition().x + 20, scrollSprite->getPosition().y + 30);
	window->draw(*scrollSprite);
	window->draw(*desc);
}

Atribute<float>* Item::add(const Atribute<float>* atribute)
{
	Atribute<float>* tmp = new Atribute<float>(atribute->getCurrent(), atribute->getMax() + stat->getMax());
	return tmp;
}

Atribute<float>* Item::restore(const Atribute<float>* atribute)
{
	Atribute<float>* tmp = new Atribute<float>(0, 0);
	tmp->setMax(atribute->getMax());
	tmp->setCurrent(atribute->getMax());
	return tmp;
}

void Item::setDescription(string description)
{
	this->description = description;
}
