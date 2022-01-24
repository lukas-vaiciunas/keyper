#pragma once

class EventQueue;

#include "DriverState.h"
#include "Image.h"
#include "Button.h"

class Menu : public DriverState
{
private:
	EventQueue &driverEventQueue_;

	Image backsplash_;

	Button playButton_;
	Button quitButton_;
public:
	Menu(EventQueue &driverEventQueue);

	void updateOnMousePress(unsigned int allegroMouseButton, int mouseX, int mouseY) override;
	void render() const override;
};