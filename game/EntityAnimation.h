#pragma once

#include <vector>
#include "Image.h"
#include "TickAlarm.h"

class EntityAnimation
{
private:
	std::vector<std::vector<Image>> frames_;
	TickAlarm updateAlarm_;
	size_t direction_;
	size_t frameIndex_;
	unsigned int numFrames_;
public:
	enum Direction : unsigned char
	{
		Down = 0,
		Up = 1,
		Left = 2,
		Right = 3
	};

	EntityAnimation(const char *sheetPath, unsigned int numFrames, unsigned int numUpdateTicks);

	void updateOnTick();

	void render(float x, float y, int allegroFlags = 0) const;

	void setDirection(Direction direction);
};