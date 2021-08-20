#include "Enemy.h"

Enemy::Enemy(Unit* hero)
{
	this->alive = true;

	if (hero != nullptr)
	{
		this->level = hero->getLevel();
	}
	else
	{
		this->level = HERO_START_LEVEL;
	}

	this->healthPoints = new Atribute<float>(50 + level * 10, 50 + level * 10);
	this->manaPoints = new Atribute<float>(0 + level * 10, 0 + level * 10);
	this->moveSpeed = new Atribute<float>(250, 250);
	this->damage = new Atribute<float>(10 + level * 3, 10 + level * 3);
	this->armor = new Atribute<float>(1 + level, 1 + level);

	loadImage();
}

Enemy::Enemy(Atribute<float>* healthPoints, Atribute<float>* manaPoints, Atribute<float>* moveSpeed, Atribute<float>* damage, Atribute<float>* armor, Unit* hero)
{
	this->alive = true;

	if (hero != nullptr)
	{
		this->level = hero->getLevel();
	}
	else
	{
		this->level = HERO_START_LEVEL;
	}

	this->healthPoints = new Atribute<float>(healthPoints->getCurrent() + level * 10, healthPoints->getMax() + level * 10);
	this->manaPoints = new Atribute<float>(manaPoints->getCurrent() + level * 10, manaPoints->getMax() + level * 10);
	this->moveSpeed = new Atribute<float>(moveSpeed->getCurrent(), moveSpeed->getMax());
	this->damage = new Atribute<float>(damage->getCurrent() + level * 3, damage->getMax() + level * 3);
	this->armor = new Atribute<float>(armor->getCurrent() + level, armor->getMax() + level);

	loadImage();
}

Enemy::Enemy(float healthPoints, float manaPoints, float moveSpeed, float damage, float armor, Unit* hero)
{
	this->alive = true;

	if (hero != nullptr)
	{
		this->level = hero->getLevel();
	}
	else
	{
		this->level = HERO_START_LEVEL;
	}

	this->healthPoints = new Atribute<float>(healthPoints + level * 10, healthPoints + level * 10);
	this->manaPoints = new Atribute<float>(manaPoints + level * 10, manaPoints + level * 10);
	this->moveSpeed = new Atribute<float>(moveSpeed, moveSpeed);
	this->damage = new Atribute<float>(damage + level * 3, damage + level * 3);
	this->armor = new Atribute<float>(armor + level, armor + level);

	loadImage();
}

Enemy::~Enemy()
{
}

const RectangleShape* Enemy::getBox() const
{
	return nullptr;
}

void Enemy::setPosition(Vector2f position)
{
	sprite->setPosition(position);
}

void Enemy::setPosition(float x, float y)
{
	sprite->setPosition(x, y);
}

void Enemy::setPosition(int tileX, int tileY)
{
	sprite->setPosition(tileX * 32 - 32, tileY * 32 - 32);
}

Text* Enemy::getText() const
{
	return health;
}

void Enemy::loadImage()
{
	image = new Image;
	image->loadFromFile(orcImagePath);

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

	health = new Text;
	font.loadFromFile("source/arial.ttf");
	health->setFont(font);
	health->setCharacterSize(14);
	health->setFillColor(Color::Red);

	update();
}

void Enemy::update()
{
	position = sprite->getPosition();
	intRect = sprite->getTextureRect();
	rect.left = static_cast<float>(intRect.left);
	rect.top = static_cast<float>(intRect.top);
	rect.width = static_cast<float>(intRect.width);
	rect.height = static_cast<float>(intRect.height);

	health->setString(to_string(static_cast<int>(healthPoints->getCurrent())));
	health->setPosition(sprite->getPosition().x + 5, sprite->getPosition().y - 20);
}