#include "gameMap.h"

const char* GameMap::EX_OUT_OF_RANGE = "Out of range";

GameMap::GameMap()
{
	nummBlock = 0;
	mapWidth = 10;
	mapHeight = 20;
	map = std::vector<std::vector<Square*>>(mapHeight);
	for (int i = 0; i < mapHeight; i++) {
		map[i] = std::vector<Square*>(mapWidth);
		for (int k = 0; k < mapWidth; k++) {
			map[i][k] = nullptr;
		}
	}
}

GameMap::GameMap(int row, int col)
{
	nummBlock = 0;
	mapHeight = row;
	mapWidth = col;
	map = std::vector<std::vector<Square*>>(mapHeight);
	for (int i = 0; i < mapHeight; i++) {
		map[i] = std::vector<Square*>(mapWidth);
		for (int k = 0; k < mapWidth; k++) {
			map[i][k] = nullptr;
			//std::cout << map[i][k] << std::endl;
		}
	}
}
GameMap::~GameMap()
{
	for (int i = mapHeight - 1; i >= 0; i--) {
		for (int j = mapWidth - 1; j >= 0; j--) {
			delete map[i][j];
		}
	}
}

bool GameMap::haveSqAt(int row, int col)
{
	if (!withIngBound(row, col)) throw EX_OUT_OF_RANGE;
	return !(map[row][col] == nullptr);
}

Square* const GameMap::getSqAt(int row, int col) {
	if (!withIngBound(row, col)) throw EX_OUT_OF_RANGE;
	return map[row][col];
}

void GameMap::addSqAt(int row, int col, int color)
{
	if (withIngBound(row, col))
	{
		if (haveSqAt(row, col)) throw  Square(row, col, squares_size, color);
		Square* newSQ = new Square(row, col, squares_size, color);
		map[row][col] = newSQ;
		nummBlock += 1;
	}
	else
	{
		throw EX_OUT_OF_RANGE;
	}
}

void GameMap::addSqAt(Square target)
{
	int row = target.getRow();
	int col = target.getCol();
	if (withIngBound(row, col))
	{
		if (haveSqAt(row, col)) throw  target;
		Square* newSQ = new Square(target);
		map[row][col] = newSQ;
		nummBlock += 1;
	}
	else
	{
		throw EX_OUT_OF_RANGE;
	}
}

void GameMap::removeSqAt(int row, int col)
{
	if (haveSqAt(row, col))
	{
		delete map[row][col];
		map[row][col] = nullptr;
	}
}

void GameMap::setSqsSize(float newSize)
{
	squares_size = newSize;
	for (int i = 0; i < mapHeight; i++) {
		for (int k = 0; k < mapWidth; k++) {
			if (map[i][k] != nullptr)map[i][k]->setSize(newSize);
		}
	}
}

//This function moves the row to be removed to the top,
// then removes each square in the row

void GameMap::removeRow(int row)
{
	if (row >= 0 && row < mapHeight)
	{
		for (int i = row; i > 0; i--)
		{
			map[i].swap(map[i - 1]);
		}
		for (int i = 0; i < mapWidth; i++) 
		{
			removeSqAt(0, i);
		}
	}
}

bool GameMap::isRowFull(int row)
{
	bool ans = true;
	if (row >= 0 && row < mapHeight) {
		for (int i = 0; i < mapWidth && ans; i++)
		{
			if (!haveSqAt(row, i)) ans = false;
		}
	}
	return ans;
}

bool GameMap::withIngBound(int row, int col) {
	return !(col < 0 || col >= mapWidth || row < 0 || row >= mapHeight);
}

//if Square at the location of target can move left or right
// then it will be moved base on dir: 1 = right, -1 = left
bool GameMap::moveSqLR(int row, int col, int dir)
{
	if (dir == 0) return true;
	if (withIngBound(row, col) &&
		withIngBound(row, col + dir) &&
		!haveSqAt(row, col + dir))
	{
		Square* temp = map[row][col];
		map[row][col] = map[row][col + dir];
		map[row][col + dir] = temp;


		if (map[row][col] != nullptr)
			map[row][col]->setCoOrd(row, col);

		if (map[row][col + dir] != nullptr)
			map[row][col + dir]->setCoOrd(row, col + dir);
		return true;
	}
	return false;
}

bool GameMap::moveSqLR(Square target, int dir)
{
	if (dir == 0) return true;
	int row = target.getRow();
	int col = target.getCol();

	if (withIngBound(row, col) &&
		withIngBound(row, col + dir) &&
		!haveSqAt(row, col + dir))
	{
		swapSq(row, col, row, col + dir);
		return true;
	}
	return false;
}

bool GameMap::moveSqDown(Square target)
{
	int row = target.getRow();
	int col = target.getCol();
	if (withIngBound(row + 1, col) && !haveSqAt(row + 1, col))
	{
		swapSq(row, col, row + 1, col);
		return true;
	}
	return false;
}

bool GameMap::moveSqDown(int row, int col)
{
	if (withIngBound(row + 1, col) && !haveSqAt(row + 1, col))
	{
		swapSq(row, col, row + 1, col);
		return true;
	}
	return false;
}

bool GameMap::swapSq(int row, int col, int row2, int col2)
{
	if (withIngBound(row, col) && withIngBound(row2, col2))
	{
		Square* temp = map[row][col];
		map[row][col] = map[row2][col2];
		map[row2][col2] = temp;


		if (map[row][col] != nullptr)map[row][col]->setCoOrd(row, col);
		if (map[row2][col2] != nullptr)map[row2][col2]->setCoOrd(row2, col2);
		return true;
	}
	return false;
}


void GameMap::fillMap(int color)
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			if (haveSqAt(i, k))
			{
				getSqAt(i, k)->setColor(color);
			}
			else {
				addSqAt(i, k, color);
			}
		}
	}
}

//THIS SHOULD BE IMPLEMENTED IN THE GRAPHIC
void GameMap::drawMap(sf::RenderWindow& window, float startX, float startY)
{
	float offset = squares_size / 5;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			if (haveSqAt(i, k))
			{
				sf::RectangleShape temp(sf::Vector2f(squares_size, squares_size));
				switch (map[i][k]->getColor())
				{
				case 0:
					temp.setFillColor(sf::Color::Red);
					break;
				case 1:
					temp.setFillColor(sf::Color::Cyan);
					break;
				case 2:
					temp.setFillColor(sf::Color::Blue);
					break;
				case 3:
					temp.setFillColor(sf::Color::Green);
					break;
				case 4:
					temp.setFillColor(sf::Color::Yellow);
					break;
				default:
					temp.setFillColor(sf::Color::White);
					break;
				}
				float xPos = startX + (squares_size + offset) * k;
				float yPos = startY + (squares_size + offset) * i;
				temp.setPosition(xPos, yPos);
				window.draw(temp);
			}
		}
	}
}

void GameMap::printToConsole(std::ostream& ouput)
{
	for (int i = 0; i < mapHeight; i++)
	{
		for (int k = 0; k < mapWidth; k++)
		{
			if (haveSqAt(i, k))
				ouput << "0 ";
			else
				ouput << "_ ";
		}
		ouput << "\n";
	}
}

int GameMap::getMapHeight()const { return mapHeight; }
int GameMap::getMapWidth()const { return mapWidth; }
