#include <allegro5/transformations.h>
#include <allegro5/allegro_primitives.h>
#include "GameStateLoss.h"
#include "Game.h"
#include "FontData.h"
#include "DriverEvent.h"
#include "Config.h"
#include "SoundBox.h"

GameStateLoss::GameStateLoss() :
	GameState()
{}

void GameStateLoss::updateOnKeyPress(Game &game, int allegroKeycode)
{
	switch (allegroKeycode)
	{
	case ALLEGRO_KEY_R:
		SoundBox::instance().playSample(2, ALLEGRO_PLAYMODE_ONCE, 1.0f);
		game.driverEventQueue_.send(new EventChangeDriverState(DriverStateType::Game));
		break;
	case ALLEGRO_KEY_Q:
		SoundBox::instance().playSample(2, ALLEGRO_PLAYMODE_ONCE, 1.0f);
		game.driverEventQueue_.send(new EventChangeDriverState(DriverStateType::Menu));
		break;
	}
}

void GameStateLoss::render(const Game &game) const
{
	ALLEGRO_TRANSFORM cameraTrans;

	al_identity_transform(&cameraTrans);
	al_scale_transform(&cameraTrans, Config::cameraScale, Config::cameraScale);
	al_translate_transform(&cameraTrans, -game.camera_.getX(), -game.camera_.getY());

	al_use_transform(&cameraTrans);
	game.level_.render();
	al_identity_transform(&cameraTrans);
	al_use_transform(&cameraTrans);

	al_draw_filled_rectangle(
		0.0f, 0.0f,
		Config::displayWidth, Config::displayHeight,
		al_map_rgba_f(0.0f, 0.0f, 0.0f, 0.75f));

	const FontData &fontData = FontData::instance();

	int mediumFontHeight = fontData.getFontLineHeight(Config::fontSizeMedium);

	fontData.renderText(
		"You Were Slain!",
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.25f,
		Config::fontSizeLarge,
		al_map_rgb(225, 225, 25),
		true,
		ALLEGRO_ALIGN_CENTER);

	fontData.renderText(
		"[r] Restart",
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.5f,
		Config::fontSizeMedium,
		al_map_rgb(225, 225, 25),
		true,
		ALLEGRO_ALIGN_CENTER);

	fontData.renderText(
		"[q] Quit to Main Menu",
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.5f + mediumFontHeight,
		Config::fontSizeMedium,
		al_map_rgb(225, 225, 25),
		true,
		ALLEGRO_ALIGN_CENTER);
}