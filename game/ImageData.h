#pragma once

#include <unordered_map>
#include "Image.h"

class ImageData
{
private:
	std::unordered_map<unsigned int, Image> images_;
public:
	ImageData() {}

	void emplace(unsigned int id, const Image &image);

	void clear();

	const Image &get(unsigned int id) const;
};