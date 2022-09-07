#pragma once

#include "GameObject.h"
#include "CustomExceptions.h"
#include <cstdlib>

using namespace std;

class Bomb : public GameObject {
private:
    int radius;
    bool ticker;
    coords* explosion;
    int explosionLength;
public:
    Bomb(int h, int w, coords s) :GameObject(9, 7, s), radius(1), ticker(false), explosion(new coords[25]), explosionLength(0) {
        if(h*w < 9)
            throw BlockEx::InvalidSpawn(false, false, 3,3);
        blockArea = new coords[9];
        numberOfBlocks = 0;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                blockArea[numberOfBlocks].row = s.row + i;
                blockArea[numberOfBlocks].col = s.col + j;
                numberOfBlocks++;
            }
        }
        coords buffer;
        for (int i = -1 * (1 + radius); i < 2 + radius; i++) {
            for (int j = -1 * (1 + radius); j < 2 + radius; j++) {
                buffer.row = s.row + i;
                buffer.col = s.col + j;
                explosion[explosionLength] = buffer;
                explosionLength++;
            }
        }
    }
    ~Bomb() {
        delete[] blockArea;
    }
    Bomb(const Bomb&) = delete;
    void shift(int rowU, int colU) override {
        GameObject::shift(rowU, colU);
        for (int i = 0; i < explosionLength; i++) {
            explosion[i].row += rowU;
            explosion[i].col += colU;
        }
    }
    int getType() override {
        ticker = !ticker;
        if (ticker) {
            return GameObject::getType();
        }
        else {
            return 6;
        }
    }
    coords* getExplosion(int i) { return i >= 0 && i < explosionLength ? &explosion[i] : nullptr; }
};