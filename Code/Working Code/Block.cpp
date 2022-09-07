#include "block.h"
#include<iostream>

using std::cerr;

//I shape = 0
//Square shape = 1
//L shape = 2
//T shape = 3
//J shape = 4
//S shape = 5
//Z shape = 6
Block::Block(int height, int width, int c, coords start) :
	GameObject(),numberOfBlocks(10), blockArea(nullptr), origin(start), color(c) {
	if (0) {
		blockArea = new coords[numberOfBlocks];
		randomSpawn(height, width, start);
	}
	else {
		blockArea = new coords[4];
		numberOfBlocks = 4;
		int shape = rand() % 7;
		color = shape;
		switch (shape) {
		case 0: // -------
			//I shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
			blockArea[2].row = start.row; blockArea[2].col = start.col - 2;
			blockArea[3].row = start.row; blockArea[3].col = start.col + 1;
			break;
		case 1:
			// square shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row - 1; blockArea[1].col = start.col - 1;
			blockArea[2].row = start.row - 1; blockArea[2].col = start.col;
			blockArea[3].row = start.row; blockArea[3].col = start.col - 1;
			break;
		case 2:
			//L shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row - 1; blockArea[1].col = start.col;
			blockArea[2].row = start.row + 1; blockArea[2].col = start.col;
			blockArea[3].row = start.row + 1; blockArea[3].col = start.col + 1;
			break;
		case 3:
			//T shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
			blockArea[2].row = start.row; blockArea[2].col = start.col + 1;
			blockArea[3].row = start.row - 1; blockArea[3].col = start.col;
			break;
		case 4:
			//J shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row - 1; blockArea[1].col = start.col;
			blockArea[2].row = start.row + 1; blockArea[2].col = start.col;
			blockArea[3].row = start.row + 1; blockArea[3].col = start.col - 1;
			break;
		case 5:
			// S shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row; blockArea[1].col = start.col-1;
			blockArea[2].row = start.row -1; blockArea[2].col = start.col;
			blockArea[3].row = start.row - 1; blockArea[3].col = start.col + 1;
			break;
		case 6:
			// Z shape
			blockArea[0].row = start.row; blockArea[0].col = start.col;
			blockArea[1].row = start.row; blockArea[1].col = start.col - 1;
			blockArea[2].row = start.row + 1; blockArea[2].col = start.col;
			blockArea[3].row = start.row + 1; blockArea[3].col = start.col +1 ;
			break;
		}
		/*blockArea = new coords[4];
		numberOfBlocks = 7;
		int shape = (rand() % 7);
		color = shape;
		for (int i = 0; i < 4; i++) {
			blockArea[i].col = SHAPES[shape][i] % 2;
			blockArea[i].row = SHAPES[shape][i] / 2;
		}*/
	}
}
void Block::updateBoundary(LL<coords>& frontier, LL<coords>& temp, int** spawn, coords buffer, int width, int height) {
	if (buffer.row > 0 && buffer.col > 0 && buffer.row < height && buffer.col < width) {
		if (spawn[buffer.row][buffer.col] == 0) {
			if (!frontier.find(buffer))
				frontier.add(buffer); // boundary can be expanded on
		}
	}
	else {
		temp.add(buffer); // fixed boundary
	}
}
void Block::randomSpawn(int height, int width, coords start) {
	int** spawn = new int*[width];
	int rOffset = start.row - height / 2;
	int cOffset = start.col - width / 2;
	for (int i = 0; i < height; i++) {
		spawn[i] = new int[width];
		for (int j = 0; j < width; j++)
			spawn[i][j] = 0;
	}
	LL<coords> temp;
	LL<coords> frontier;
	frontier.add(start);
	for (int i = 0; i < numberOfBlocks; i++) {
		try {
			blockArea[i] = frontier.remove(rand() % (frontier.getSize()));
			start = blockArea[i];
			spawn[start.row][start.col] = 1;
		}
		catch (const char* err) {
			cerr << err;
			return;
		}
		start.row -= 1; // checkBottom
		updateBoundary(frontier, temp, spawn, start, width, height);
		start.row += 2; // checkTop
		updateBoundary(frontier, temp, spawn, start, width, height);
		start.row -= 1;
		start.col -= 1; // check left
		updateBoundary(frontier, temp, spawn, start, width, height);
		start.col += 2; // check Right
		updateBoundary(frontier, temp, spawn, start, width, height);
	}
	// resize to original
	for (int i = 0; i < numberOfBlocks; i++) {
		blockArea[i].row += rOffset;
		blockArea[i].col += cOffset;
	}
	for (int i = 0; i < height; i++)
		delete[] spawn[i];
	delete[] spawn;
}

void Block::update(int rowU, int colU) {
	for (int i = 0; i < numberOfBlocks; i++) {
		blockArea[i].row += rowU;
		blockArea[i].col += colU;
	}
	origin.row += rowU;
	origin.col += colU;
}
void Block::rotateCW() {
	int temp;
	for (int i = 0; i < numberOfBlocks; i++) {
		temp = origin.row - blockArea[i].row;
		blockArea[i].row = origin.row - (origin.col - blockArea[i].col);
		blockArea[i].col = origin.col + temp;
	}
}

ostream& operator<<(ostream& out, const Block& blk) {
	int maxW = -1;
	int maxH = -1;
	for (int i = 0; i < blk.numberOfBlocks; i++) {
		if (maxW < blk.blockArea[i].col)
			maxW = blk.blockArea[i].col;
		if (maxH < blk.blockArea[i].row)
			maxH = blk.blockArea[i].row;
	}
	maxW++; maxH++;
	int** temp = new int*[maxH];
	for (int i = 0; i < maxH; i++) {
		temp[i] = new int[maxW];
		for (int j = 0; j < maxW; j++) {
			temp[i][j] = 0;
		}
	}
	for (int i = 0; i < blk.numberOfBlocks; i++) {
		temp[blk.blockArea[i].row][blk.blockArea[i].col] = 1;
	}
	out << "---------------BlockObject----------------" << endl;
	for (int i = 0; i < maxH; i++) {
		for (int j = 0; j < maxW; j++) {
			if (temp[i][j] == 0)
				out << " ";
			else
				out << temp[i][j];
		}
		out << endl;
	}
	out << "-------------------------------" << endl;
	for (int i = 0; i < maxH; i++)
		delete[] temp[i];
	delete[] temp;
	return out;
}
