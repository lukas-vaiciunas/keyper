#pragma once

#include "EntityAnimation.h"

class Entity
{
private:
	EntityAnimation animation_;
	int col_;
	int row_;
protected:
	void setCol_(int col);
	void setRow_(int row);
	
	EntityAnimation &getAnimation_();
public:
	Entity(int col, int row, const char *animationSheetPath);
	virtual ~Entity() {}

	void updateOnTick();

	void render() const;

	int getCol() const;
	int getRow() const;
};