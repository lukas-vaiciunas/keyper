#pragma once

#include "GameState.h"

class GameStatePause : public GameState
{
public:
	GameStatePause();

	void updateOnKeyPress(Game &game, int allegroKeycode) override;

	void render(const Game &game) const override;
};