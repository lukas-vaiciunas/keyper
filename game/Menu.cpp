#include "Menu.h"
#include "FontData.h"
#include "Config.h"
#include "EventQueue.h"
#include "DriverEvent.h"
#include "SoundBox.h"
#include "Config.h"

Menu::Menu(EventQueue &driverEventQueue) :
	DriverState(),
	driverEventQueue_(driverEventQueue),
	backsplash_("img/backsplash.png"),
	playButton_(
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.5f,
		Config::fontSizeMedium,
		"play"),
	quitButton_(
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.65f,
		Config::fontSizeMedium,
		"quit")
{}

void Menu::updateOnMousePress(unsigned int allegroMouseButton, int mouseX, int mouseY)
{
	if (allegroMouseButton & 1)
	{
		if (playButton_.isHovered(mouseX, mouseY))
		{
			SoundBox::instance().playSample(2, ALLEGRO_PLAYMODE_ONCE, 1.0f);
			driverEventQueue_.send(new EventChangeDriverState(DriverStateType::Game));
		}
		else if (quitButton_.isHovered(mouseX, mouseY))
		{
			SoundBox::instance().playSample(2, ALLEGRO_PLAYMODE_ONCE, 1.0f);
			driverEventQueue_.send(new EventQuit());
		}
	}
}

void Menu::render() const
{
	ALLEGRO_TRANSFORM backsplashTrans;
	al_identity_transform(&backsplashTrans);
	al_scale_transform(&backsplashTrans, Config::cameraScale, Config::cameraScale);
	al_translate_transform(&backsplashTrans, Config::displayWidth * 0.5f - backsplash_.getWidth() * Config::cameraScale * 0.5f, Config::displayHeight * 0.5f - backsplash_.getHeight() * Config::cameraScale * 0.5f);

	al_use_transform(&backsplashTrans);
	backsplash_.render(0.0f, 0.0f);
	al_identity_transform(&backsplashTrans);
	al_use_transform(&backsplashTrans);

	FontData::instance().renderText(
		"Keyper",
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.3f,
		Config::fontSizeMedium,
		al_map_rgb(225, 225, 25),
		true,
		ALLEGRO_ALIGN_CENTER);

	playButton_.render();
	quitButton_.render();

	FontData::instance().renderText(
		"Created by Lukas Vaiciunas",
		0.0f,
		Config::displayHeight - FontData::instance().getFontLineHeight(Config::fontSizeSmall),
		Config::fontSizeSmall,
		al_map_rgb(225, 225, 25),
		false,
		ALLEGRO_ALIGN_LEFT);
}