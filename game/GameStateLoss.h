#pragma once

#include "GameState.h"

class GameStateLoss : public GameState
{
public:
	GameStateLoss();

	void updateOnKeyPress(Game &game, int allegroKeycode) override;

	void render(const Game &game) const override;
};