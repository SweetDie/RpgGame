#include"Hero.h"
#include"Diamonds.h"
#include"MyText.h"
#include"Enemy.h"
#include"Dealer.h"
#include"Shop.h"

int main()
{
	bool shopOpen = false;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Survival");
	Hero* hero = new Hero(100, 200, 300, 20, 2);
	Map* map = new Map;
	Shop* shop = new Shop;
	Clock* clock = new Clock;
	View* view = new View;

	shop->addItem(new Item(5, -1, "img/hpR.png", "Restore HP\nCost: 5", 1));
	shop->addItem(new Item(5, -1, "img/mpR.png", "Restore MP\nCost: 5", 2));
	shop->addItem(new Item(10, 10, "img/hp.png", "HP + 10\nCost: 10", 3));
	shop->addItem(new Item(7, 20, "img/mp.png", "MP + 20\nCost: 7", 4));

	view->setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	view->setCenter(0 + WINDOW_WIDTH / 2, map->getHeightPx() - WINDOW_HEIGHT / 2);

	vector<Enemy*> enemies;
	for (size_t i = 0; i < 4; i++)
	{
		enemies.push_back(new Enemy(hero));
	}

	enemies[0]->setPosition(4, 20);
	enemies[1]->setPosition(9, 21);
	enemies[2]->setPosition(3, 10);
	enemies[3]->setPosition(15, 4);

	MyText myText(hero, view);
	Dealer* dealer = new Dealer;
	while (window.isOpen())
	{
		//----------------------- END GAME
		if (hero->getAlive() == false)
		{
			window.close();
		}
		//----------------------- END GAME

		Event event;

		window.clear();

		clock->restart();

		map->drawBackground(&window);
		window.draw(*dealer->getSprite());
		window.draw(*hero->getSprite());
		map->drawTopground(&window);

		window.setView(*view);

		myText.draw(&window);

		shop->sprite.setPosition(hero->getPosition());

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::E && hero->getSprite()->getGlobalBounds().intersects(dealer->getSprite()->getGlobalBounds()))
				{
					shopOpen = !shopOpen;
				}
			}
		}
		if (!hero->getSprite()->getGlobalBounds().intersects(dealer->getSprite()->getGlobalBounds()))
		{
			shopOpen = false;
		}
		if (shopOpen)
		{
		shop->draw(&window);
		//cout << item->sprite.getPosition().x << endl;
		}

		for (auto i : shop->items)
		{
			if (i.sprite->getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y + (40 * 32 - view->getSize().y)))
			{
				i.draw(&window);
				if (Mouse::isButtonPressed(Mouse::Button::Left))
				{
					if (i.id == 1 && i.cost <= *hero->getGold())
					{
						hero->setHealthPoints(i.restore(&hero->getHealthPoints()));
						*hero->getGold() -= i.cost;
					}
					else if (i.id == 2 && i.cost <= *hero->getGold())
					{
						hero->setManaPoints(i.restore(&hero->getManaPoints()));
						*hero->getGold() -= i.cost;
					}
					else if (i.id == 3 && i.cost <= *hero->getGold())
					{
						hero->setHealthPoints(i.add(&hero->getHealthPoints()));
						*hero->getGold() -= i.cost;
					}
					else if (i.id == 4 && i.cost <= *hero->getGold())
					{
						hero->setManaPoints(i.add(&hero->getManaPoints()));
						*hero->getGold() -= i.cost;
					}
					sleep(Time(milliseconds(100)));
				}
			}
		}

		//cout << "Mouse::" <<Mouse::getPosition(window).x << endl;

		for (auto i : enemies)
		{
			i->update();
			window.draw(*i->getSprite());
			window.draw(*i->getText());
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			hero->move(clock, Unit::Direction::Right, map);
			if (hero->getPosition().x > view->getCenter().x + WINDOW_WIDTH / 2)
			{
				view->move(map->getWidthPx() - view->getSize().x, 0);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::L))
		{
			hero->move(clock, Unit::Direction::Left, map);
			if (hero->getPosition().x < view->getCenter().x - WINDOW_WIDTH / 2)
			{
				view->move(-(map->getWidthPx() - view->getSize().x), 0);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			hero->move(clock, Unit::Direction::Down, map);
			if (hero->getPosition().y > view->getCenter().y + WINDOW_HEIGHT / 2)
			{
				view->move(0, map->getHeightPx() - view->getSize().y);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			hero->move(clock, Unit::Direction::Up, map);
			if (hero->getPosition().y < view->getCenter().y - WINDOW_HEIGHT / 2)
			{
				view->move(0, -(map->getHeightPx() - view->getSize().y));
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::E))
		{
			hero->action(map, &window, &enemies);
			map->update();
		}
		window.display();
	}
	return 0;
}