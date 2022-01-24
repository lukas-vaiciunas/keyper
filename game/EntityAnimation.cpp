#include <allegro5/bitmap_io.h>
#include "EntityAnimation.h"
#include "Config.h"

EntityAnimation::EntityAnimation(const char *sheetPath, unsigned int numFrames, unsigned int numUpdateTicks) :
	frames_(4, std::vector<Image>({})),
	updateAlarm_(numUpdateTicks),
	direction_(Direction::Down),
	frameIndex_(0),
	numFrames_(numFrames)
{
	ALLEGRO_BITMAP *sheet = al_load_bitmap(sheetPath);

	frames_[Direction::Down] = {
		Image(sheet, 0, 0, Config::assetRes, Config::assetRes),
		Image(sheet, Config::assetRes, 0, Config::assetRes, Config::assetRes) };

	frames_[Direction::Up] = {
		Image(sheet, 0, Config::assetRes, Config::assetRes, Config::assetRes),
		Image(sheet, Config::assetRes, Config::assetRes, Config::assetRes, Config::assetRes) };

	frames_[Direction::Left] = {
		Image(sheet, 0, Config::assetRes * 2, Config::assetRes, Config::assetRes),
		Image(sheet, Config::assetRes, Config::assetRes * 2, Config::assetRes, Config::assetRes) };

	frames_[Direction::Right] = {
		Image(sheet, 0, Config::assetRes * 3, Config::assetRes, Config::assetRes),
		Image(sheet, Config::assetRes, Config::assetRes * 3, Config::assetRes, Config::assetRes) };

	al_destroy_bitmap(sheet);
}

void EntityAnimation::updateOnTick()
{
	updateAlarm_.updateOnTick();
	if (updateAlarm_.isAlarm())
	{
		updateAlarm_.reset();
		frameIndex_ = (frameIndex_ + 1) % numFrames_;
	}
}

void EntityAnimation::render(float x, float y, int allegroFlags) const
{
	frames_[direction_][frameIndex_].render(x, y, allegroFlags);
}

void EntityAnimation::setDirection(Direction direction)
{
	direction_ = direction;
}