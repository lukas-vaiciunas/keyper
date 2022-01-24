#include "TickAlarm.h"

TickAlarm::TickAlarm(unsigned int targetNumTicks) :
	targetNumTicks_(targetNumTicks),
	numTicks_(0)
{}

void TickAlarm::updateOnTick()
{
	++numTicks_;
}

void TickAlarm::reset()
{
	numTicks_ = 0;
}

bool TickAlarm::isAlarm() const
{
	return numTicks_ >= targetNumTicks_;
}