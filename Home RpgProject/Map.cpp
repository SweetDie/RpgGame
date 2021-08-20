#include "Map.h"

Map::Map()
{
	image = new Image;
	image->loadFromFile(mapImagePath);

	texture = new Texture;
	texture->loadFromImage(*image);

	sprite = new Sprite;
	sprite->setTexture(*texture);

	load();
}

Map::~Map()
{
	for (auto i : map)
	{
		for (auto j : i)
		{
			for (auto l : j)
			{
				if (l != nullptr)
				{
					delete l;
				}
			}
		}
	}
}

int Map::getWidth() const
{
	return width;
}

int Map::getHeight() const
{
	return height;
}

int Map::getWidthPx() const
{
	return width * tileWidth;
}

int Map::getHeightPx() const
{
	return height * tileHeight;
}

int Map::getTileWidth() const
{
	return tileWidth;
}

int Map::getTileHeight() const
{
	return tileHeight;
}

Sprite* Map::getSprite()
{
	return sprite;
}

Image* Map::getImage()
{
	return image;
}

void Map::drawBackground(RenderWindow* window)
{
	for (int layer = 0; layer < 2; layer++)
	{
		for (int x = 0; x < height; x++)
		{
			for (int y = 0; y < width; y++)
			{
				if (map[layer][x][y] == nullptr)
				{
					continue;
				}
				sprite->setTextureRect(map[layer][x][y]->getIntRect());
				sprite->setPosition(y * tileWidth, x * tileWidth);
				window->draw(*sprite);
			}
		}
	}
	for (auto i : resources)
	{
		int x = ((i->getGid() % (image->getSize().x / tileWidth)) - 1) * tileWidth;
		int y = (i->getGid() / (image->getSize().x / tileWidth)) * tileHeight;
		sprite->setTextureRect(IntRect(x, y, tileWidth, tileHeight));
		sprite->setPosition(i->getRect().left, i->getRect().top);
		window->draw(*sprite);
	}
}

void Map::drawTopground(RenderWindow* window)
{
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			if (map[2][x][y] == nullptr)
			{
				continue;
			}
			sprite->setTextureRect(map[2][x][y]->getIntRect());
			sprite->setPosition(y * tileWidth, x * tileWidth);
			window->draw(*sprite);
		}
	}
}

void Map::update()
{
	auto itRes = resources.begin();
	while (itRes != resources.end())
	{
		if (!(*itRes)->getAlive())
		{
			delete (*itRes);
			itRes = resources.erase(itRes);
		}
		if (itRes != resources.end())
			itRes++;
	}
}

void Map::load()
{
	TiXmlDocument* doc = new TiXmlDocument;
	if (!doc->LoadFile(mapTilesPath.c_str()))
	{
		throw exception("not loaded map.xml file");
	}
	else
	{
		TiXmlElement* settings;
		settings = doc->FirstChildElement();
		this->width = atoi(settings->Attribute("width"));
		this->height = atoi(settings->Attribute("height"));
		this->tileWidth = atoi(settings->Attribute("tilewidth"));
		this->tileHeight = atoi(settings->Attribute("tileheight"));

		TiXmlElement* layer;
		vector<string> tiles;
		layer = doc->FirstChildElement()->FirstChildElement("layer");
		while (layer)
		{
			TiXmlElement* tile;
			tile = layer->FirstChildElement("data");
			while (tile)
			{
				tiles.push_back(tile->GetText());
				tile = tile->NextSiblingElement("data");
			}
			layer = layer->NextSiblingElement("layer");
		}
		setBackgorund(tiles);

		// #################################### Objects ############################
		TiXmlElement* objectgroup;
		objectgroup = doc->FirstChildElement()->FirstChildElement("objectgroup");
		while (objectgroup)
		{
			TiXmlElement* object;
			object = objectgroup->FirstChildElement("object");
			while (object)
			{
				float x = stof(object->Attribute("x"));
				float y = stof(object->Attribute("y"));
				float width = stof(object->Attribute("width"));
				float height = stof(object->Attribute("height"));
				FloatRect rect(x, y, width, height);
				if(strcmp(object->Attribute("type"), "Solid") == 0)
				{
					objects.push_back(new SolidObject(&rect));
				}
				else if (strcmp(object->Attribute("type"), "Diamond") == 0)
				{
					int gid = atoi(object->Attribute("gid"));
					resources.push_back(new Diamonds(&rect, gid));
				}
				else if (strcmp(object->Attribute("type"), "Gold") == 0)
				{
					int gid = atoi(object->Attribute("gid"));
					resources.push_back(new Gold(&rect, gid));
				}
				else if (strcmp(object->Attribute("type"), "Wood") == 0)
				{
					int gid = atoi(object->Attribute("gid"));
					resources.push_back(new Wood(&rect, gid));
				}
				object = object->NextSiblingElement("object");
			}
			objectgroup = objectgroup->NextSiblingElement("objectgroup");
		}
		// #################################### Objects ############################
	}
	delete doc;
}

bool Map::colision(RectangleShape* shape)
{
	for (auto i : objects)
	{
		if (shape->getGlobalBounds().intersects(i->getRect()))
			return true;
	}
	return false;
}

void Map::setBackgorund(vector<string> tiles)
{
	int x = 0;
	int y = 0;

	for (auto i : tiles)
	{
		vector<vector<Object*>> X;
		vector<Object*> Y;
		string tmpStr = "";
		for (auto str : i)
		{
			if (str >= '0' && str <= '9')
			{
				tmpStr += str;
			}
			else if (str == ',')
			{
				if (tmpStr == "0")
				{
					Y.push_back(nullptr);
					tmpStr = "";
					y++;
				}
				else
				{
					IntRect rect(((atoi(tmpStr.c_str()) % (image->getSize().x / tileWidth)) - 1) * tileWidth, (atoi(tmpStr.c_str()) / (image->getSize().x / tileWidth)) * tileHeight, tileWidth, tileHeight);
					FloatRect fRect;
					fRect.left = static_cast<float>(rect.left);
					fRect.top = static_cast<float>(rect.top);
					fRect.width = static_cast<float>(rect.width);
					fRect.height = static_cast<float>(rect.height);
					Y.push_back(new BackgroundObject(&fRect));
					tmpStr = "";
					y++;
				}
				if (x == 39 && y == 50)
				{
					X.push_back(Y);
					x++;
					y = 0;
					Y.clear();
				}
			}
			else if(str == ' ')
			{
				X.push_back(Y);
				x++;
				y = 0;
				Y.clear();
			}
		}
		map.push_back(X);
		x = 0;
	}
}
