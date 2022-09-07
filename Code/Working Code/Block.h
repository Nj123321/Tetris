#pragma once

#include "GameObject.h"
#include "LinkedList.h"
#include <cstdlib>
#include <iostream>

using namespace std;

class Block: public GameObject{
    private:
        int numberOfBlocks;
        coords* blockArea;
        coords origin;
        int color;
        void updateBoundary(LL<coords>& frontier, LL<coords>& temp, int** spawn, coords buffer, int width, int height);
        void randomSpawn(int height, int width, coords start);
    public:
        Block(int height, int width, int c, coords start);
        ~Block(){
            delete[] blockArea;
        }
        Block(const Block& ) = delete;
        void update(int rowU, int colU);
        void rotateCW() override;
        coords* getCoords(int i) override{return (i < numberOfBlocks && i >= 0)? &blockArea[i] : nullptr;}
        int getType() override{return color;}
        
        friend ostream& operator<<(ostream& out, const Block& blk);
};