#pragma once

class Game;

class GameState
{
public:
	GameState() {}
	~GameState() {}

	virtual void updateOnTick(Game &game) {}
	virtual void updateOnKeyPress(Game &game, int allegroKeycode) {}

	virtual void render(const Game &game) const {}
};