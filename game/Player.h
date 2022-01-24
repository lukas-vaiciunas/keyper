#pragma once

class Level;
class EventQueue;

#include "Entity.h"

class Player : public Entity
{
private:
	bool moved_;
public:
	Player(int col, int row, const char *animationSheetPath);

	void updateOnKeyPress(int allegroKeycode, Level &level, EventQueue &gameEventQueue);

	void setCol(int col);
	void setRow(int row);

	bool moved() const;
};