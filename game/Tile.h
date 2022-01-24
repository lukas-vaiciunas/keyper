#pragma once

class ImageData;

#include "Image.h"

class Tile
{
private:
	unsigned int col_;
	unsigned int row_;
	unsigned int imageId_;
public:
	Tile(unsigned int col, unsigned int row, unsigned int imageId);
	virtual ~Tile() {}

	void render(const ImageData &imageData) const;
};