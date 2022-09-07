#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
public:
	virtual void update(int, int) = 0;
	virtual void rotateCW() = 0;
	virtual int* getBounds() = 0;
	virtual coords* getCoords(int) = 0;
	virtual int getSpawned() = 0;
};

#endif
