#pragma once
#include"SolidObject.h"
#include"BackgroundObject.h"
#include"Diamonds.h"
#include"Gold.h"
#include"Wood.h"

class Map
{
public:
	Map();
	~Map();

	int getWidth() const;
	int getHeight() const;
	int getWidthPx() const;
	int getHeightPx() const;
	int getTileWidth() const;
	int getTileHeight() const;
	Sprite* getSprite();
	Image* getImage();

	void drawBackground(RenderWindow* window);
	void drawTopground(RenderWindow* window);
	void update();
	void load();
	bool colision(RectangleShape* shape);

	vector<vector<vector<Object*>>> map;
	vector<Object*> objects;
	vector<Resources*> resources;
private:
	int width;
	int height;
	int tileWidth;
	int tileHeight;

	Image* image;
	Texture* texture;
	Sprite* sprite;

	void setBackgorund(vector<string> tiles);
};

