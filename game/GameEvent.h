#pragma once

#include "Event.h"

class EventLevelComplete : public Event
{
public:
	EventLevelComplete() :
		Event(EventType::LevelComplete)
	{}
};

class EventLoss : public Event
{
public:
	EventLoss() :
		Event(EventType::Loss)
	{}
};