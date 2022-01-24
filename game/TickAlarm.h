#pragma once

class TickAlarm
{
private:
	unsigned int targetNumTicks_;
	unsigned int numTicks_;
public:
	TickAlarm(unsigned int targetNumTicks);

	void updateOnTick();

	void reset();

	bool isAlarm() const;
};