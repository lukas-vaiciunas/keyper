#include <allegro5/bitmap_io.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/allegro_opengl.h>
#include "Image.h"

Image::Image(const char *path) :
	bitmap_(al_load_bitmap(path)),
	width_(al_get_bitmap_width(bitmap_)),
	height_(al_get_bitmap_height(bitmap_))
{
	al_convert_mask_to_alpha(bitmap_, al_map_rgb(255, 0, 255));
}

Image::Image(
	ALLEGRO_BITMAP *sheet,
	unsigned int sX, unsigned int sY,
	unsigned char sWidth, unsigned char sHeight)
	:
	bitmap_(al_create_bitmap(sWidth, sHeight)),
	width_(sWidth),
	height_(sHeight)
{
	al_set_target_bitmap(bitmap_);
	al_draw_bitmap_region(sheet, sX, sY, sWidth, sHeight, 0.0f, 0.0f, 0);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));

	al_convert_mask_to_alpha(bitmap_, al_map_rgb(255, 0, 255));
}

Image::Image(const Image &other)
{
	this->copy_(other);
}

Image &Image::operator=(const Image &other)
{
	al_destroy_bitmap(bitmap_);

	this->copy_(other);

	return *this;
}

Image::~Image()
{
	al_destroy_bitmap(bitmap_);
}

void Image::render(float x, float y, int allegroFlags) const
{
	al_draw_bitmap(bitmap_, x, y, allegroFlags);
}

unsigned char Image::getWidth() const
{
	return width_;
}

unsigned char Image::getHeight() const
{
	return height_;
}

void Image::copy_(const Image &other)
{
	bitmap_ = al_create_bitmap(other.width_, other.height_);
	width_ = other.width_;
	height_ = other.height_;

	al_set_target_bitmap(bitmap_);
	al_draw_bitmap(other.bitmap_, 0.0f, 0.0f, 0);
	al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}