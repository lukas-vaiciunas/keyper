#pragma once

#include "GameState.h"

class GameStatePlay : public GameState
{
public:
	GameStatePlay();

	void updateOnTick(Game &game) override;
	void updateOnKeyPress(Game &game, int allegroKeycode) override;

	void render(const Game &game) const override;
};