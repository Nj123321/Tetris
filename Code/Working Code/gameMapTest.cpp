#include "SFML/Graphics.hpp"
#include "gameMap.h"
#include <iostream>
#include <string>

using namespace sf;
using std::cout;
using std::endl;
using std::string;



int main()
{
	sf::Vector2u renderWindowSize{ 840u, 875u };	// length width
	RenderWindow window(VideoMode(840, 875), "Tetris", sf::Style::Close);
	Event event;
	auto loopCounter = 0u;

	GameMap	gm = GameMap(25,24);	//row col 
	RectangleShape sq(Vector2f(30.0f, 30.0f));
	sq.setFillColor(Color::Red);

	Vector2i blockpos(0, 12);
	gm.addSqAt(blockpos.x, blockpos.y, sq);
	gm.addSqAt((blockpos.x)+1, blockpos.y, sq);
	gm.addSqAt((blockpos.x)+1, (blockpos.y)+1, sq);
	gm.addSqAt((blockpos.x)+1, (blockpos.y)+2, sq);
	gm.drawMap(window, 0.0f, 0.0f);

	while (window.isOpen())
	{
		loopCounter++;
		if (!(loopCounter % 1800))
		{
			if (((blockpos.x)+ 2) < gm.getMapHeight())
			{
				gm.removeSqAt(blockpos.x, blockpos.y);
				gm.removeSqAt((blockpos.x) + 1, blockpos.y);
				gm.removeSqAt((blockpos.x) + 1, (blockpos.y) + 1);
				gm.removeSqAt((blockpos.x) + 1, (blockpos.y) + 2);

				blockpos.x += 1;
				
				gm.addSqAt(blockpos.x, blockpos.y, sq);
				gm.addSqAt((blockpos.x) + 1, blockpos.y, sq);
				gm.addSqAt((blockpos.x) + 1, (blockpos.y) + 1, sq);
				gm.addSqAt((blockpos.x) + 1, (blockpos.y) + 2, sq);
			}
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			default:
				;
			}
		}

		window.clear();
		gm.drawMap(window, 0.0f, 0.0f);
		window.display();
	}
}
