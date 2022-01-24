#pragma once

class GameState;

#include "DriverState.h"
#include "Listener.h"
#include "Player.h"
#include "Level.h"
#include "Camera.h"
#include "EventQueue.h"
#include "GameStateType.h"

class Game :
	public DriverState,
	public Listener
{
private:
	friend class GameStatePlay;
	friend class GameStatePause;
	friend class GameStateLoss;

	GameState *state_;

	EventQueue &driverEventQueue_;

	EventQueue eventQueue_;
	Player player_;
	Level level_;
	Camera camera_;

	unsigned int turnNum_;
	unsigned int levelNum_;

	void centerCameraOnPlayer_();
	void changeState_(GameStateType stateType);
public:
	Game(EventQueue &driverEventQueue);
	~Game();

	void onEvent(const Event &ev) override;

	void updateOnTick() override;
	void updateOnKeyPress(int allegroKeycode) override;

	void render() const override;
};