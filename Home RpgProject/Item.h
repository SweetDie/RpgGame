#pragma once
#include"Constants.h"
#include"Defines.h"
#include"Atribute.h"

class Item
{
public:
	Item(int cost, Atribute<float>* stat, string path, int id);
	Item(int cost, Atribute<float>* stat, string path, string description, int id);
	Item(int cost, float stat, string path, int id);
	Item(int cost, float stat, string path, string description, int id);
	~Item();

	void load(string path);
	void draw(RenderWindow* window);
	Atribute<float>* add(const Atribute<float>* atribute);
	Atribute<float>* restore(const Atribute<float>* atribute);
	void setDescription(string description);

	Atribute<float>* stat;
	sf::Image* image;
	sf::Texture* texture;
	sf::Sprite* sprite;
	int cost;
	string description;
	int id;

	Image* scrollImage;
	Texture* scrollTexture;
	Sprite* scrollSprite;
	Font font;
	Text* desc;
};

