#pragma once

#include "GameObject.h"
#include "LinkedList.h"
#include "CustomExceptions.h"
#include <cstdlib>

using namespace std;

class RandomBlock : public GameObject {
private:
    void updateBoundary(LL<coords>&, LL<coords>&, bool*, coords, int, int);
    coords prevUpdate;
public:
    RandomBlock() = delete;
    RandomBlock(int, int, int, coords, int = 5);
    ~RandomBlock() = default;
    RandomBlock(const RandomBlock&) = delete;
    void shift(int, int) override;
    void undoShift() { GameObject::shift(-1*prevUpdate.row, -1*prevUpdate.col); }
    int getType() override { return color; };
};