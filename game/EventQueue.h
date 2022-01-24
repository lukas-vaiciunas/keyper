#pragma once

class Event;
class Listener;

#include <queue>

class EventQueue
{
private:
	std::queue<Event *> queue_;
	std::vector<Listener *> listeners_;
public:
	EventQueue();
	~EventQueue();

	void dispatch();

	void send(Event *ev);

	void attach(Listener *listener);
};