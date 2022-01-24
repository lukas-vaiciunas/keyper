#include "Entity.h"
#include "Config.h"

Entity::Entity(int col, int row, const char *animationSheetPath) :
	animation_(animationSheetPath, 2, 30),
	col_(col),
	row_(row)
{}

void Entity::updateOnTick()
{
	animation_.updateOnTick();
}

void Entity::render() const
{
	animation_.render(col_ * Config::assetRes, row_ * Config::assetRes);
}

int Entity::getCol() const
{
	return col_;
}

int Entity::getRow() const
{
	return row_;
}

void Entity::setCol_(int col)
{
	col_ = col;
}

void Entity::setRow_(int row)
{
	row_ = row;
}

EntityAnimation &Entity::getAnimation_()
{
	return animation_;
}