#include "Tile.h"
#include "ImageData.h"
#include "Config.h"

Tile::Tile(unsigned int col, unsigned int row, unsigned int imageId) :
	col_(col),
	row_(row),
	imageId_(imageId)
{}

void Tile::render(const ImageData &imageData) const
{
	imageData.get(imageId_).render(col_ * Config::assetRes, row_ * Config::assetRes);
}