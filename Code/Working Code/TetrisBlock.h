#pragma once

#include "GameObject.h"
#include "CustomExceptions.h"
#include <cstdlib>
#include <iostream>

using namespace std;

class TetrisBlock : public GameObject {
public:
    TetrisBlock();
    TetrisBlock(int height, int width, int c, coords start);
    ~TetrisBlock() {
        delete[] blockArea;
    }
    TetrisBlock(const TetrisBlock&) = delete;
};