#pragma once

#include "Tile.h"

class Key : public Tile
{
private:
	unsigned int doorSpatialHash_;
public:
	Key(
		unsigned int col,
		unsigned int row,
		unsigned int imageId,
		unsigned int doorSpatialHash);

	unsigned int doorSpatialHash() const;
};