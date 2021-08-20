#include "MyText.h"

MyText::MyText(View* view)
{
	this->hero = nullptr;
	resourceDiamonds = new Text;
	resourceGolds = new Text;
	resourceWoods = new Text;
	healthPoints = new Text;
	manaPoints = new Text;
	this->view = view;
	this->position = new Vector2f(view->getCenter().x - WINDOW_WIDTH / 2, view->getCenter().y - WINDOW_HEIGHT / 2);
	font.loadFromFile("source/arial.ttf");
	update();
}

MyText::MyText(Hero* hero, View* view)
{
	this->hero = hero;
	resourceDiamonds = new Text;
	resourceGolds = new Text;
	resourceWoods = new Text;
	healthPoints = new Text;
	manaPoints = new Text;
	this->view = view;
	this->position = new Vector2f(view->getCenter().x - WINDOW_WIDTH / 2, view->getCenter().y - WINDOW_HEIGHT / 2);
	font.loadFromFile("source/arial.ttf");
	update();
}

MyText::MyText(Vector2f position, Hero* hero, View* view)
{
	this->hero = hero;
	this->position = new Vector2f(position);
	resourceDiamonds = new Text;
	resourceGolds = new Text;
	resourceWoods = new Text;
	healthPoints = new Text;
	manaPoints = new Text;
	this->view = view;
	font.loadFromFile("source/arial.ttf");
	update();
}

void MyText::setPosition(Vector2f position)
{
	*this->position = position;
}

void MyText::setPosition(float x, float y)
{
	this->position->x = x;
	this->position->y = y;
}

void MyText::draw(RenderWindow* window)
{
	update();
	window->draw(*resourceDiamonds);
	window->draw(*resourceGolds);
	window->draw(*resourceWoods);
	window->draw(*healthPoints);
	window->draw(*manaPoints);
}

void MyText::update()
{
	this->position = new Vector2f(view->getCenter().x - WINDOW_WIDTH / 2, view->getCenter().y - WINDOW_HEIGHT / 2);

	resourceDiamonds->setFont(font);
	resourceDiamonds->setCharacterSize(14);
	resourceDiamonds->setFillColor(Color::White);
	if(hero != nullptr)
		resourceDiamonds->setString("Diamonds: " + to_string(hero->diamondNumber));
	resourceDiamonds->setPosition(*position);

	resourceGolds->setFont(font);
	resourceGolds->setCharacterSize(14);
	resourceGolds->setFillColor(Color::White);
	if (hero != nullptr)
		resourceGolds->setString("Golds: " + to_string(hero->goldNumber));
	resourceGolds->setPosition((*position).x, (*position).y + 16);

	resourceWoods->setFont(font);
	resourceWoods->setCharacterSize(14);
	resourceWoods->setFillColor(Color::White);
	if (hero != nullptr)
		resourceWoods->setString("Woods: " + to_string(hero->woodNumber));
	resourceWoods->setPosition((*position).x, (*position).y + 32);

	healthPoints->setFont(font);
	healthPoints->setCharacterSize(14);
	healthPoints->setFillColor(Color::Red);
	if (hero != nullptr)
		healthPoints->setString("Health: " + to_string(static_cast<int>(hero->healthPoints->getCurrent())) + "/" + to_string(static_cast<int>(hero->healthPoints->getMax())));
	healthPoints->setPosition((*position).x, (*position).y + 48);

	manaPoints->setFont(font);
	manaPoints->setCharacterSize(14);
	manaPoints->setFillColor(Color::Blue);
	if (hero != nullptr)
		manaPoints->setString("Mana: " + to_string(static_cast<int>(hero->manaPoints->getCurrent())) + "/" + to_string(static_cast<int>(hero->manaPoints->getMax())));
	manaPoints->setPosition((*position).x, (*position).y + 64);
}
