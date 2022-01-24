#include "ImageData.h"

void ImageData::emplace(unsigned int id, const Image &image)
{
	images_.emplace(id, image);
}

void ImageData::clear()
{
	images_.clear();
}

const Image &ImageData::get(unsigned int id) const
{
	return images_.find(id)->second;
}