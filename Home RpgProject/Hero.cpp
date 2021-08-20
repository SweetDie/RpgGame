#include "Hero.h"

Hero::Hero(Atribute<float>* healthPoints, Atribute<float>* manaPoints, Atribute<float>* moveSpeed, Atribute<float>* damage, Atribute<float>* armor)
{
	this->healthPoints = new Atribute<float>(healthPoints->getCurrent(), healthPoints->getMax());
	this->manaPoints = new Atribute<float>(manaPoints->getCurrent(), manaPoints->getMax());
	this->moveSpeed = new Atribute<float>(moveSpeed->getCurrent(), moveSpeed->getMax());
	this->damage = new Atribute<float>(damage->getCurrent(), damage->getMax());
	this->armor = new Atribute<float>(armor->getCurrent(), armor->getMax());
	this->level = HERO_START_LEVEL;
	this->alive = true;
	this->experience = new Atribute<float>(0, HERO_EXPERIENCE_FOR_LEVEL_UP);
	this->mineDamage = new Atribute<int>(50, 50);

	this->armorFactor = HERO_LEVEL_UP_FACTOR;
	this->damageFactor = HERO_LEVEL_UP_FACTOR;
	this->healthPointsFactor = HERO_LEVEL_UP_FACTOR;
	this->manaPointsFactor = HERO_LEVEL_UP_FACTOR;
	this->moveSpeedFactor = HERO_LEVEL_UP_FACTOR;

	woodNumber = 0;
	goldNumber = 0;
	diamondNumber = 0;

	loadAnimation();
	loadImage();
}

Hero::Hero(float healthPoints, float manaPoints, float moveSpeed, float damage, float armor)
{
	this->healthPoints = new Atribute<float>(healthPoints, healthPoints);
	this->manaPoints = new Atribute<float>(manaPoints, manaPoints);
	this->moveSpeed = new Atribute<float>(moveSpeed, moveSpeed);
	this->damage = new Atribute<float>(damage, damage);
	this->armor = new Atribute<float>(armor, armor);
	this->level = HERO_START_LEVEL;
	this->alive = true;
	this->experience = new Atribute<float>(0, HERO_EXPERIENCE_FOR_LEVEL_UP);
	this->mineDamage = new Atribute<int>(50, 50);

	this->armorFactor = HERO_LEVEL_UP_FACTOR;
	this->damageFactor = HERO_LEVEL_UP_FACTOR;
	this->healthPointsFactor = HERO_LEVEL_UP_FACTOR;
	this->manaPointsFactor = HERO_LEVEL_UP_FACTOR;
	this->moveSpeedFactor = HERO_LEVEL_UP_FACTOR;

	woodNumber = 0;
	goldNumber = 0;
	diamondNumber = 0;

	loadAnimation();
	loadImage();
}

Hero::~Hero()
{
	delete healthPoints;
	delete manaPoints;
	delete moveSpeed;
	delete damage;
	delete armor;
	delete experience;
	delete image;
	delete texture;
	delete sprite;
	delete mineDamage;
}

const RectangleShape* Hero::getBox() const
{
	return unitBox;
}

bool Hero::addSkill(Skill skill)
{
	if (skills.size() >= HERO_MAX_NUMBER_SKILLS)
	{
		return false;
	}
	else
	{
		bool flag = true;
		for (auto i : skills)
		{
			if (i.getName() == skill.getName())
				flag = false;
		}
		if (flag)
		{
			skills.push_back(skill);
			return flag;
		}
		return flag;
	}
}

void Hero::levelUp()
{
	healthPoints->levelUp(healthPointsFactor);
	manaPoints->levelUp(manaPointsFactor);
	damage->levelUp(damageFactor);
	armor->levelUp(armorFactor);
	this->level++;
	this->experience->setMax(this->level * HERO_EXPERIENCE_FOR_LEVEL_UP);
	this->experience->setCurrent(NULL);
}

void Hero::loadAnimation()
{
	TiXmlDocument* doc = new TiXmlDocument(heroAnimationFilePath.c_str());
	if (!doc->LoadFile())
	{
		throw exception("not loaded animation file");
	}
	else
	{
		TiXmlElement* animation;
		animation = doc->FirstChildElement()->FirstChildElement("animation");
		while (animation)
		{
			TiXmlElement* cut;
			cut = animation->FirstChildElement("cut");
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));
				if (strcmp(animation->Attribute("title"), "up") == 0) animationList[Animation::MoveUp].push_back(IntRect(x, y, w, h));
				else if (strcmp(animation->Attribute("title"), "down") == 0) animationList[Animation::MoveDown].push_back(IntRect(x, y, w, h));
				else if (strcmp(animation->Attribute("title"), "right") == 0) animationList[Animation::MoveRight].push_back(IntRect(x, y, w, h));
				else if (strcmp(animation->Attribute("title"), "left") == 0) animationList[Animation::MoveLeft].push_back(IntRect(x, y, w, h));
				else if (strcmp(animation->Attribute("title"), "run") == 0) animationList[Animation::Run].push_back(IntRect(x, y, w, h));
				else if (strcmp(animation->Attribute("title"), "attack") == 0) animationList[Animation::Attack].push_back(IntRect(x, y, w, h));
				else if (strcmp(animation->Attribute("title"), "die") == 0) animationList[Animation::Die].push_back(IntRect(x, y, w, h));

				cut = cut->NextSiblingElement("cut");
			}
			animation = animation->NextSiblingElement("animation");
		}
	}
}

void Hero::loadImage()
{
	image = new Image;
	image->loadFromFile(heroImagePath);

	texture = new Texture;
	texture->loadFromImage(*image);

	sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setTextureRect(animationList[0][0]);

	sprite->setPosition(HERO_START_POSITION_X * 32 - 32, HERO_START_POSITION_Y * 32 - 32);

	Vector2f size(sprite->getTextureRect().width - 15, 15);
	unitBox = new RectangleShape(size);

	position = sprite->getPosition();
	intRect = sprite->getTextureRect();
	rect.left = static_cast<float>(intRect.left);
	rect.top = static_cast<float>(intRect.top);
	rect.width = static_cast<float>(intRect.width);
	rect.height = static_cast<float>(intRect.height);

	update();
}

void Hero::move(Clock* clock, Direction rotation, Map* map)
{
	static float currentFrame = 0;
	int speed = clock->getElapsedTime().asMicroseconds();
	speed /= (SPEED_START - moveSpeed->getCurrent()) * SPEED_FACTOR;

	RectangleShape tmp = *unitBox;

	if (rotation == Direction::Up)
	{
		tmp.setPosition(unitBox->getPosition().x, unitBox->getPosition().y - 0.1 * speed);
		if (map->colision(&tmp))
		{
			update();
			return;
		}
		else
		{
			sprite->move(0, -0.1 * speed);
			update();
		}
		currentFrame += 0.005 * speed;
		if (currentFrame > animationList[Animation::MoveUp].size())
		{
			currentFrame -= animationList[Animation::MoveUp].size();
		}
		sprite->setTextureRect(animationList[Animation::MoveUp][currentFrame]);
	}
	else if (rotation == Direction::Down)
	{
		tmp.setPosition(unitBox->getPosition().x, unitBox->getPosition().y + 0.1 * speed);
		if (map->colision(&tmp))
		{
			update();
			return;
		}
		else
		{
			sprite->move(0, 0.1 * speed);
			update();
		}
		currentFrame += 0.005 * speed;
		if (currentFrame > animationList[Animation::MoveDown].size())
		{
			currentFrame -= animationList[Animation::MoveDown].size();
		}
		sprite->setTextureRect(animationList[Animation::MoveDown][currentFrame]);
	}
	else if (rotation == Direction::Right)
	{
		tmp.setPosition(unitBox->getPosition().x + 0.1 * speed, unitBox->getPosition().y);
		if (map->colision(&tmp))
		{
			update();
			return;
		}
		else
		{
			sprite->move(0.1 * speed, 0);
			update();
		}
		currentFrame += 0.005 * speed;
		if (currentFrame > animationList[Animation::MoveRight].size())
		{
			currentFrame -= animationList[Animation::MoveRight].size();
		}
		sprite->setTextureRect(animationList[Animation::MoveRight][currentFrame]);
	}
	else if (rotation == Direction::Left)
	{
		tmp.setPosition(unitBox->getPosition().x - 0.1 * speed, unitBox->getPosition().y);
		if (map->colision(&tmp))
		{
			update();
			return;
		}
		else
		{
			sprite->move(-0.1 * speed, 0);
			update();
		}
		currentFrame += 0.005 * speed;
		if (currentFrame > animationList[Animation::MoveLeft].size())
		{
			currentFrame -= animationList[Animation::MoveLeft].size();
		}
		sprite->setTextureRect(animationList[Animation::MoveLeft][currentFrame]);
	}
	update();
}

void Hero::update()
{
	if (moveSpeed->getMax() > SPEED_MAX)
	{
		moveSpeed->set(SPEED_MAX, SPEED_MAX);
	}
	position = sprite->getPosition();
	intRect = sprite->getTextureRect();
	rect.left = static_cast<float>(intRect.left);
	rect.top = static_cast<float>(intRect.top);
	rect.width = static_cast<float>(intRect.width);
	rect.height = static_cast<float>(intRect.height);
	unitBox->setPosition(sprite->getPosition().x + ((sprite->getTextureRect().width - unitBox->getSize().x) / 2), sprite->getPosition().y + sprite->getTextureRect().height - unitBox->getSize().y);
}

void Hero::action(Map* map, RenderWindow* window, vector<Enemy*>* enemies)
{
	for (auto i : map->resources)
	{
		if (sprite->getGlobalBounds().intersects(i->getRect()))
		{
			if (dynamic_cast<Gold*>(i))
			{
				goldNumber += i->mine(mineDamage->getCurrent());
			}
			else if (dynamic_cast<Wood*>(i))
			{
				woodNumber += i->mine(mineDamage->getCurrent());
			}
			else if (dynamic_cast<Diamonds*>(i))
			{
				diamondNumber += i->mine(mineDamage->getCurrent());
			}
			for (int anim = 0; anim < animationList[Animation::Attack].size(); anim++)
			{
				map->drawBackground(window);
				sprite->setTextureRect(animationList[Animation::Attack][anim]);
				window->draw(*sprite);
				map->drawTopground(window);
				window->display();
				sleep(Time(milliseconds(50)));
			}
			sprite->setTextureRect(animationList[Animation::MoveRight][0]);
			return;
		}
	}

	for (auto i : *enemies)
	{
		if (sprite->getGlobalBounds().intersects(i->getSprite()->getGlobalBounds()))
		{
			if (attack(i) == 1)
			{
				auto itEnemy = enemies->begin();
				while (itEnemy != enemies->end())
				{
					if (!(*itEnemy)->getAlive())
					{
						delete (*itEnemy);
						itEnemy = enemies->erase(itEnemy);
					}
					if (itEnemy != enemies->end())
						itEnemy++;
				}
			}
			for (int anim = 0; anim < animationList[Animation::Attack].size(); anim++)
			{
				map->drawBackground(window);
				sprite->setTextureRect(animationList[Animation::Attack][anim]);
				window->draw(*sprite);
				map->drawTopground(window);
				for (auto i : *enemies)
				{
					window->draw(*i->getSprite());
				}

				window->display();
				sleep(Time(milliseconds(50)));
			}
			sprite->setTextureRect(animationList[Animation::MoveRight][0]);

			return;
		}
	}
}

int* Hero::getGold()
{
	return &goldNumber;
}

int* Hero::getWood()
{
	return &woodNumber;
}

int* Hero::getDiamond()
{
	return &diamondNumber;
}

void Hero::setLevelFactor(double healthPointsFactor, double manaPointsFactor, float moveSpeedFactor, double damageFactor, double armorFactor)
{
	this->armorFactor = armorFactor;
	this->damageFactor = damageFactor;
	this->moveSpeedFactor = moveSpeedFactor;
	this->healthPointsFactor = healthPointsFactor;
	this->manaPointsFactor = manaPointsFactor;
}