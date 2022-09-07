#include "SFML/Graphics.hpp"
#include "gameMap.h"
#include "block.h"
#include <iostream>
#include <string>

using namespace sf;
using std::cout;
using std::endl;
using std::string;

bool checkCollision(GameMap& map, LL<coords>& list, coords& coor);
bool checkLeft(GameMap& map, LL<coords>& list, coords& coor);
bool checkRight(GameMap& map, LL<coords>& list, coords& coor);
void moveBlocks(string direction, GameMap& map, LL<coords>& list, coords& coor, int color);
void rotateCW(GameMap& map, GameObject*& obj, LL<coords>& list, coords& coor, int color);
void checkForFinishedRow(GameMap& map, GameObject*& obj, coords spawn, const coords coor, LL<coords>& list, int& color);


int main()
{
	sf::Vector2u renderWindowSize{ 735u, 880u };	// length width
	RenderWindow window(VideoMode(735, 880), "Tetris", sf::Style::Close);
	Event event;
	auto loopCounter = 0u;

	GameMap	map = GameMap(18, 15);	//row col 

	coords spawn;
	spawn.row = 0; 
	spawn.col = 8;
	LL<coords> list;
	
	srand(static_cast<unsigned>(time(nullptr)));
	GameObject* obj = new Block(map, 2, 3, spawn, list);
	coords coor;
	int color = rand() % 5;

	Node<coords>* temp = list.getHead();
	for (int i = 0; i < list.getSize(); i++)
	{
		coor = temp->value;
		map.addSqAt(coor.row, coor.col, color);
		temp = temp->next;
	}

	map.drawMap(window, 0.0f, 0.0f);

	while (window.isOpen())
	{
		loopCounter++;
		if (!(loopCounter % 1100))
		{
			checkForFinishedRow(map, obj, spawn, coor, list, color);

			temp = list.getHead();
			int maxrow = coor.row;

			for (int i = 0; i < list.getSize(); i++)
			{
				coor = temp->value;
				if (coor.row > maxrow)
					maxrow = coor.row;
				temp = temp->next;
			}

			for (int i = 0; i < map.getMapWidth(); i++)
			{
				if (map.haveSqAt(0, i))
				{
					list.removeAll();
					delete obj;
					obj = nullptr;
					break;
				}
			}

			if (obj != nullptr)
			{
				if ((maxrow + 1) < map.getMapHeight()) {
					try
					{
						if (checkCollision(map, list, coor))
						{
							list.removeAll();
							delete obj;
							obj = nullptr;
							if (maxrow > 2 && maxrow - 1 > 2)
							{
								srand(static_cast<unsigned>(time(nullptr)));
								obj = new Block(map, 2, 3, spawn, list);
								temp = list.getHead();
								color = rand() % 5;
								for (int i = 0; i < list.getSize(); i++)
								{
									coor = temp->value;
									map.addSqAt(coor.row, coor.col, color);
									temp = temp->next;
								}
							}
						}

						else
						{
							temp = list.getHead();
							for (int i = 0; i < list.getSize(); i++)
							{
								coor = temp->value;
								map.removeSqAt(coor.row, coor.col);
								temp->value.row++;
								coor.row = temp->value.row;
								temp = temp->next;
							}

							temp = list.getHead();
							for (int i = 0; i < list.getSize(); i++)
							{
								coor = temp->value;
								map.addSqAt(coor.row, coor.col, color);
								temp = temp->next;
							}
						}	
					}
					catch (const char* err)
					{
						cout << err << endl;
					}
				}

				else
				{
					try
					{
						list.removeAll();
						delete obj;
						obj = nullptr;
						srand(static_cast<unsigned>(time(nullptr)));
						obj = new Block(map, 2, 3, spawn, list);
						temp = list.getHead();
						color = rand() % 5;
						for (int i = 0; i < list.getSize(); i++)
						{
							coor = temp->value;
							map.addSqAt(coor.row, coor.col, color);
							temp = temp->next;
						}
					}
					catch (const char* err)
					{
						cout << err << endl;
					}
				}
			}
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					moveBlocks("down", map, list, coor, color);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					moveBlocks("left", map, list, coor, color);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					moveBlocks("right", map, list, coor, color);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					rotateCW(map, obj, list, coor, color);
				else;
			default:
				;
			}
		}

		window.clear();
		map.drawMap(window, 0.0f, 0.0f);
		window.display();
	}
}

bool checkCollision(GameMap& map, LL<coords>& list , coords& coor)
{
	Node<coords>* iter = list.getHead();
	for (int i = 0; i < list.getSize(); i++)
	{
		coor = iter->value;
		coords temp;
		temp.row = coor.row;
		temp.col = coor.col;
		temp.row++;
		if (!list.find(temp))
		{
			try
			{
				if (map.haveSqAt(coor.row, coor.col) && map.haveSqAt((coor.row + 1), coor.col))
					return true;
				coor.row++;
			}
			catch (const char* err)
			{
				cout << err << endl;
			}	
		}	
		iter = iter->next;
	}
	return false;
}

bool checkLeft(GameMap& map, LL<coords>& list, coords& coor)
{
	Node<coords>* iter = list.getHead();
	for (int i = 0; i < list.getSize(); i++)
	{
		coor = iter->value;
		coords temp;
		temp.row = coor.row;
		temp.col = coor.col;
		temp.col--;
		if (!list.find(temp))
		{
			try
			{
				if (map.haveSqAt(coor.row, coor.col) && map.haveSqAt(coor.row, (coor.col - 1)))
					return true;
				coor.col--;
			}
			catch (const char* err)
			{
				cout << err << endl;
			}
		}
		iter = iter->next;
	}
	return false;
}

bool checkRight(GameMap& map, LL<coords>& list, coords& coor)
{
	Node<coords>* iter = list.getHead();
	for (int i = 0; i < list.getSize(); i++)
	{
		coor = iter->value;
		coords temp;
		temp.row = coor.row;
		temp.col = coor.col;
		temp.col++;
		if (!list.find(temp))
		{
			try
			{
				if (map.haveSqAt(coor.row, coor.col) && map.haveSqAt(coor.row, (coor.col + 1)))
					return true;
				coor.col++;
			}
			catch (const char* err)
			{
				cout << err << endl;
			}
		}
		iter = iter->next;
	}
	return false;
}

void moveBlocks(string direction, GameMap& map, LL<coords>& list, coords& coor, int color)
{
	Node<coords>* iter = list.getHead();
	int maxrow = coor.row;
	int leftcol = coor.col;
	int rightcol = coor.col;

	for (int i = 0; i < list.getSize(); i++)
	{
		coor = iter->value;
		if (coor.row > maxrow)
			maxrow = coor.row;
		if (coor.col < leftcol)
			leftcol = coor.col;
		if (coor.col > rightcol)
			rightcol = coor.col;
		iter = iter->next;
	}

	Node<coords>* temp;

	if (direction == "down")
	{
		if ((maxrow + 1) < map.getMapHeight())
		{
			if (!checkCollision(map, list, coor))
			{
				try 
				{
					for (int i = 0; i < map.getMapWidth(); i++)
					{
						if (map.haveSqAt(0, i))
						{
							return;
						}
					}

					temp = list.getHead();
					for (int i = 0; i < list.getSize(); i++)
					{
						coor = temp->value;
						map.removeSqAt(coor.row, coor.col);
						temp->value.row++;
						coor.row = temp->value.row;
						temp = temp->next;
					}

					temp = list.getHead();
					for (int i = 0; i < list.getSize(); i++)
					{
						coor = temp->value;
						map.addSqAt(coor.row, coor.col, color);
						temp = temp->next;
					}
				}
				catch(const char* err)
				{
					cout << err << endl;
				}
			}
		}
	}

	else if (direction == "left")
	{
		if ((leftcol - 1) >= 0)
		{
			if (!checkLeft(map, list, coor))
			{
				try
				{
					for (int i = 0; i < map.getMapWidth(); i++)
					{
						if (map.haveSqAt(0, i))
						{
							return;
						}
					}

					temp = list.getHead();
					for (int i = 0; i < list.getSize(); i++)
					{
						coor = temp->value;
						map.removeSqAt(coor.row, coor.col);
						temp->value.col--;
						coor.col = temp->value.col;
						temp = temp->next;
					}

					temp = list.getHead();
					for (int i = 0; i < list.getSize(); i++)
					{
						coor = temp->value;
						map.addSqAt(coor.row, coor.col, color);
						temp = temp->next;
					}
				}
				catch (const char* err)
				{
					cout << err << endl;
				}
			}
		}
	}

	else if (direction == "right")
	{
		if ((rightcol + 1) < map.getMapWidth())
		{
			if (!checkRight(map, list, coor))
			{
				try
				{
					for (int i = 0; i < map.getMapWidth(); i++)
					{
						if (map.haveSqAt(0, i))
						{
							return;
						}
					}

					temp = list.getHead();
					for (int i = 0; i < list.getSize(); i++)
					{
						coor = temp->value;
						map.removeSqAt(coor.row, coor.col);
						temp->value.col++;
						coor.col = temp->value.col;
						temp = temp->next;
					}

					temp = list.getHead();
					for (int i = 0; i < list.getSize(); i++)
					{
						coor = temp->value;
						map.addSqAt(coor.row, coor.col, color);
						temp = temp->next;
					}
				}
				catch (const char* err)
				{
					cout << err << endl;
				}
			}
		}
	}
}

void rotateCW(GameMap& map, GameObject*& obj, LL<coords>& list, coords& coor, int color)
{
	Node<coords>* iter = list.getHead();
	coords temp;
	temp.row = coor.row;
	temp.col = coor.col;

	int maxrow = coor.row;
	int minrow = coor.row;
	int leftcol = coor.col;
	int rightcol = coor.col;

	for (int i = 0; i < list.getSize(); i++)
	{
		if (iter->value.row > maxrow)
			maxrow = iter->value.row;
		if (iter->value.row < minrow)
			minrow = iter->value.row;
		if (iter->value.col < leftcol)
			leftcol = iter->value.col;
		if (iter->value.col > rightcol)
			rightcol = iter->value.col;
		iter = iter->next;
	}

	int midcol = (leftcol + rightcol) / 2;
	
	if (map.withIngBound(coor.row, coor.col) && !checkCollision(map, list, coor)
		&& (maxrow + 2) < map.getMapHeight() && (maxrow - 2) > 0
		&& rightcol < map.getMapWidth() && (leftcol - 2) >= 0
		&& !checkLeft(map, list, coor) && !checkRight(map, list, coor))
	{
		try
		{
			iter = list.getHead();
			for (int i = 0; i < list.getSize(); i++)
			{
				map.removeSqAt(iter->value.row, iter->value.col);
				iter = iter->next;
			}

			iter = list.getHead();
			for (int i = 0; i < list.getSize(); i++)
			{
				temp.row = minrow + iter->value.col - midcol;
				temp.col = midcol - (iter->value.row - minrow);
				iter->value.row = temp.row;
				iter->value.col = temp.col;
				iter = iter->next;
			}
		}
		catch (const char* err)
		{
			cout << err << endl;
		}
	}

	else
		return;

	int count = 0;
	iter = list.getHead();
	for (int i = 0; i < list.getSize(); i++)
	{
		coor = iter->value;
		if (!map.haveSqAt(coor.row, coor.col) && !checkCollision(map, list, coor))
		{
			count++;
		}
		iter = iter->next;
	}

	try 
	{
		iter = list.getHead();

		if (count == list.getSize())
		{
			iter = list.getHead();
			for (int i = 0; i < list.getSize(); i++)
			{
				coor = iter->value;
				map.addSqAt(coor.row, coor.col, color);
				iter = iter->next;
			}
		}

		else
		{
			for (int i = 0; i < list.getSize(); i++)
			{
				coor = iter->value;
				coor.row = temp.row;
				coor.col = temp.col;
				iter = iter->next;
			}

			iter = list.getHead();
			for (int i = 0; i < list.getSize(); i++)
			{
				coor = iter->value;
				map.addSqAt(coor.row, coor.col, color);
				iter = iter->next;
			}
		}
	}
	catch (const char* err)
	{
		cout << err << endl;
	}
}

void checkForFinishedRow(GameMap& map, GameObject*& obj, coords spawn, const coords coor, LL<coords>& list, int& color)
{
	const int mapH = map.getMapHeight();
	Node<coords>* iter = list.getHead();
	coords temp;
	temp.row = coor.row;
	temp.col = coor.col;
	int count = 0;
	int i = 0;
	for(int i = 0; i < mapH; i++)
	{
		if (map.isRowFull(i) && (temp.row == (mapH - 1) || (checkCollision(map, list, temp) && list.find(temp))))
		{
			map.removeRow(i);
			count++;
		}
	}

	if (count > 0)
	{
		list.removeAll();
		delete obj;
		obj = nullptr;
		srand(static_cast<unsigned>(time(nullptr)));
		obj = new Block(map, 2, 3, spawn, list);
	}
}
