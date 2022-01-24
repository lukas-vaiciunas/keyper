#include <allegro5/transformations.h>
#include <allegro5/keycodes.h>
#include "GameStatePlay.h"
#include "Game.h"
#include "Config.h"
#include "SoundBox.h"

GameStatePlay::GameStatePlay() :
	GameState()
{}

void GameStatePlay::updateOnTick(Game &game)
{
	game.player_.updateOnTick();
	game.level_.updateOnTick();
}

void GameStatePlay::updateOnKeyPress(Game &game, int allegroKeycode)
{
	if (allegroKeycode == ALLEGRO_KEY_ESCAPE)
	{
		SoundBox::instance().playSample(2, ALLEGRO_PLAYMODE_ONCE, 1.0f);
		game.changeState_(GameStateType::Pause);
	}
	else
	{
		game.player_.updateOnKeyPress(allegroKeycode, game.level_, game.eventQueue_);
		game.centerCameraOnPlayer_();

		if (game.player_.moved())
		{
			if (++game.turnNum_ >= 3)
			{
				game.turnNum_ = 1;
				game.level_.updateOnTurn(game.player_.getCol(), game.player_.getRow(), game.eventQueue_);
			}
		}
	}
}

void GameStatePlay::render(const Game &game) const
{
	ALLEGRO_TRANSFORM cameraTrans;

	al_identity_transform(&cameraTrans);
	al_scale_transform(&cameraTrans, Config::cameraScale, Config::cameraScale);
	al_translate_transform(&cameraTrans, -game.camera_.getX(), -game.camera_.getY());

	al_use_transform(&cameraTrans);
	game.level_.render();
	game.player_.render();
	al_identity_transform(&cameraTrans);
	al_use_transform(&cameraTrans);
}