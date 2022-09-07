#pragma once

#include "SFML/Graphics.hpp"
#include "square.h"
#include <vector>
#include <iostream>

class GameMap
{
private:
	//map is a 2D array to store all square block of the game
	//Coordinates are from top to bot, left to right
	//When a coord does not have a square it will be null ptr
	//color = 0 - red | 1 - white| .....
	std::vector< std::vector<Square*>> map;

	int mapWidth = 10, mapHeight = 20, nummBlock = 0;
	float squares_size = 40.0f;
	int colors[5] = { 0,1,2,3,4 };

	static const char* EX_OUT_OF_RANGE; //used coord that is out of range

public:
	GameMap();
	GameMap(int row, int col);
	~GameMap();

	int getMapHeight()const;
	int getMapWidth()const;

	//turn on and off square
	void addSqAt(int row, int col, int color);
	void addSqAt(Square target);
	void removeSqAt(int row, int col);
	Square* const getSqAt(int row, int col);
	void setSqsSize(float newSize);

	//some special functions
	bool moveSqLR(Square target, int dir);//1 = right, -1 = left
	bool moveSqLR(int row, int col, int dir);

	bool moveSqDown(Square target);//asdasdasdasd
	bool moveSqDown(int row, int col);//asdasdasdsadas
	bool swapSq(int row, int col, int row2, int col2);

	void drawMap(sf::RenderWindow& window, float startX, float startY);
	void printToConsole(std::ostream& ouput);
	void fillMap(int color);

	//Check condition functions
	bool haveSqAt(int row, int col);
	bool withIngBound(int row, int col);
	void removeRow(int row);
	bool isRowFull(int row);
};
