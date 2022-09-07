#pragma once

#include "SFML/Graphics.hpp"
#include "square.h"
#include "TetrisBlock.h"
#include "RandomBlock.h"
#include "Bomb.h"
#include "CustomExceptions.h"
#include <vector>
#include <iostream>
#include <fstream>

class GameMap
{
private:
	//map is a 2D array to store all square block of the game
	//Coordinates are from top to bot, left to right
	//When a coord does not have a square it will be null ptr
	//color = 0 - red | 1 - white| .....
	std::vector< std::vector<Square*> > map;

	int mapHeight, mapWidth, spawnH;
	float squares_size = 50.0f;
	int colors[4] = { 0,2,3,4 };

	// helper functions
	void addSqAt(int row, int col, int color);
	void removeSqAt(int row, int col);
	Square* getSqAt(int row, int col);
	bool haveSqAt(int row, int col);
	bool withIngBound(int row, int col);
	bool shiftObj(GameObject*, int, int);
	void undoChanges(GameObject*, coords, int, int);
	int update();

public:
	GameMap(int = 20, int = 10, int = 4);
	~GameMap();

	GameObject* spawn();
	void rotate(GameObject*);
	int updateObj(GameObject*, int, int, int&);

	void setSqsSize(float newSize);
	void drawMap(sf::RenderWindow&, float, float, float);
	void fillMap(int);

	bool loadSaveFile(string);
	bool writeSaveFile(string, GameObject* ptr);

	int getMapHeight()const { return mapHeight; }
	int getMapWidth()const { return mapWidth; }

	friend ofstream& operator<<(ofstream& out, const GameMap& m);
	friend ifstream& operator>>(ifstream& out, GameMap& m);
};
