#include "Driver.h"
#include "DriverState.h"
#include "Menu.h"
#include "Game.h"
#include "DriverEvent.h"

Driver::Driver() :
	Listener({ EventType::ChangeDriverState, EventType::Quit }),
	state_(nullptr),
	eventQueue_()
{
	eventQueue_.attach(this);

	this->changeState_(DriverStateType::Menu);
}

Driver::~Driver()
{
	this->changeState_(DriverStateType::None);
}

void Driver::onEvent(const Event &ev)
{
	if (ev.type() == EventType::ChangeDriverState)
	{
		const EventChangeDriverState &trueEv = static_cast<const EventChangeDriverState &>(ev);

		this->changeState_(trueEv.getDriverStateType());
	}
	else if (ev.type() == EventType::Quit)
	{
		isDone_ = true;
	}
}

void Driver::updateOnTick()
{
	eventQueue_.dispatch();

	state_->updateOnTick();
}

void Driver::updateOnMousePress(unsigned int allegroMouseButton, int mouseX, int mouseY)
{
	state_->updateOnMousePress(allegroMouseButton, mouseX, mouseY);
}

void Driver::updateOnKeyPress(int allegroKeycode)
{
	state_->updateOnKeyPress(allegroKeycode);
}

void Driver::render() const
{
	state_->render();
}

void Driver::sendEvent(Event *ev)
{
	eventQueue_.send(ev);
}

bool Driver::isDone() const
{
	return isDone_;
}

void Driver::changeState_(DriverStateType stateType)
{
	delete state_;

	switch (stateType)
	{
	case DriverStateType::Menu:
		state_ = new Menu(eventQueue_);
		break;
	case DriverStateType::Game:
		state_ = new Game(eventQueue_);
		break;
	}
}