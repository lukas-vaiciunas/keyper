#pragma once

class DriverState;

#include "Listener.h"
#include "EventQueue.h"
#include "DriverStateType.h"

class Driver : public Listener
{
private:
	DriverState *state_;

	EventQueue eventQueue_;

	bool isDone_;

	void changeState_(DriverStateType stateType);
public:
	Driver();
	~Driver();

	void onEvent(const Event &ev) override;

	void updateOnTick();
	void updateOnMousePress(unsigned int allegroMouseButton, int mouseX, int mouseY);
	void updateOnKeyPress(int allegroKeycode);

	void render() const;

	void sendEvent(Event *ev);

	bool isDone() const;
};