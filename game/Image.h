#pragma once

#include <allegro5/bitmap.h>

class Image
{
private:
	ALLEGRO_BITMAP *bitmap_;
	unsigned char width_;
	unsigned char height_;

	void copy_(const Image &other);
public:
	Image(const char *path);
	Image(
		ALLEGRO_BITMAP *sheet,
		unsigned int sX, unsigned int sY,
		unsigned char sWidth, unsigned char sHeight);
	Image(const Image &other);
	Image &operator=(const Image &other);
	~Image();

	void render(float x, float y, int allegroFlags = 0) const;

	unsigned char getWidth() const;
	unsigned char getHeight() const;
};