#pragma once

#ifndef BLOCK_H
#define BLOCK_H

#include "gameMap.h"
#include "coords.h"
#include "gameObject.h"
#include "linkedlist.h"
#include<iostream>
#include<string>

using std::string;
using std::cerr;


class Block : public GameObject {
private:
	const static int numberOfBlocks = 4;
	coords* blockArea;
	int* bounds;
	int boundSize;
	coords origin;
	bool find(coords find) {
		for (int i = 0; i < numberOfBlocks; i++) {
			if (blockArea[i] == find)
				return true;
		}
		return false;
	}
public:
	Block(GameMap& board, int width, int height, coords start, LL<coords>& frontier) :
		blockArea(new coords[numberOfBlocks]), bounds(new int[board.getMapWidth()]), boundSize(board.getMapHeight()), origin(start) {
		for (int i = 0; i < 4; i++) { bounds[i] = -1; blockArea[i].row = 0; blockArea[i].col = 0; }
		blockArea[0] = start;
		bounds[start.col] = start.row;
		coords temp;
		for (int i = 0; i < numberOfBlocks - 1; i++) {
			temp = blockArea[i];
			temp.row += 1;
			if (!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) < height) && (abs(temp.col - start.col) < width))
				frontier.add(temp);
			temp.row += 1;
			if (!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) < height) && (abs(temp.col - start.col) < width))
				frontier.add(temp);
			temp.row -= 1;
			temp.col -= 1;
			if (!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) < height) && (abs(temp.col - start.col) < width))
				frontier.add(temp);
			temp.col += 2;
			if (!frontier.find(temp) && !find(temp) && (abs(temp.row - start.row) < height) && (abs(temp.col - start.col) < width))
				frontier.add(temp);
			try {
				blockArea[i + 1] = frontier.randomlyRemove(rand() % (frontier.getSize()));
			}
			catch (string err) {
				cerr << err;
				return;
			}
			if (blockArea[i + 1].row > bounds[blockArea[i + 1].col])
				bounds[blockArea[i + 1].col] = blockArea[i + 1].row;
		}
	}
	~Block() {
		delete[] bounds;
		delete[] blockArea;
		bounds = nullptr;
		blockArea = nullptr;
	}
	void update(int rowU, int colU) override {
		for (int i = 0; i < numberOfBlocks; i++) {
			blockArea[i].row += rowU;
			blockArea[i].col += colU;
		}
		for (int i = 0; i < boundSize; i++) {
			if (bounds[i] != -1)
				bounds[i + colU] = bounds[i] + rowU;
		}
	}
	int* getBounds() override { return bounds; }
	coords* getCoords(int i) override { return (i < numberOfBlocks && i >= 0) ? &blockArea[i] : nullptr; }
	int getSpawned() override { return numberOfBlocks; }
};

#endif
