#include "Key.h"

Key::Key(
	unsigned int col,
	unsigned int row,
	unsigned int imageId,
	unsigned int doorSpatialHash)
	:
	Tile(col, row, imageId),
	doorSpatialHash_(doorSpatialHash)
{}

unsigned int Key::doorSpatialHash() const
{
	return doorSpatialHash_;
}