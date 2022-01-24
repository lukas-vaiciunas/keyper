#include "EventQueue.h"
#include "Listener.h"
#include "Event.h"

EventQueue::EventQueue() :
	listeners_({})
{}

EventQueue::~EventQueue()
{
	while (!queue_.empty())
	{
		delete queue_.front();
		queue_.pop();
	}
}

void EventQueue::dispatch()
{
	if (queue_.empty())
		return;

	const Event &ev = *queue_.front();

	for (Listener *const listener : listeners_)
		if(listener->acceptsEventType(ev.type()))
			listener->onEvent(ev);

	delete queue_.front();
	queue_.pop();
}

void EventQueue::send(Event *ev)
{
	queue_.push(ev);
}

void EventQueue::attach(Listener *listener)
{
	listeners_.push_back(listener);
}