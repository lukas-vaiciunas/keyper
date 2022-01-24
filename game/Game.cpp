#include <allegro5/transformations.h>
#include "Game.h"
#include "Event.h"
#include "Config.h"
#include "GameStatePlay.h"
#include "GameStatePause.h"
#include "GameStateLoss.h"
#include "SoundBox.h"

Game::Game(EventQueue &driverEventQueue) :
	DriverState(),
	Listener({ EventType::LevelComplete, EventType::Loss }),
	state_(nullptr),
	driverEventQueue_(driverEventQueue),
	eventQueue_(),
	player_(0, 0, "img/sheet-player-8.png"),
	level_(1),
	camera_(0.0f, 0.0f),
	turnNum_(1),
	levelNum_(1)
{
	eventQueue_.attach(this);

	this->changeState_(GameStateType::Play);

	player_.setCol(level_.getPlayerSpawnCol());
	player_.setRow(level_.getPlayerSpawnRow());

	this->centerCameraOnPlayer_();
}

Game::~Game()
{
	delete state_;
}

void Game::onEvent(const Event &ev)
{
	switch (ev.type())
	{
	case EventType::LevelComplete:
		SoundBox::instance().playSample(5, ALLEGRO_PLAYMODE_ONCE, 1.0f);
		level_ = Level(++levelNum_);
		player_.setCol(level_.getPlayerSpawnCol());
		player_.setRow(level_.getPlayerSpawnRow());
		turnNum_ = 1;

		this->centerCameraOnPlayer_();
		break;
	case EventType::Loss:
		SoundBox::instance().playSample(6, ALLEGRO_PLAYMODE_ONCE, 1.0f);
		this->changeState_(GameStateType::Loss);
		break;
	}
}

void Game::updateOnTick()
{
	state_->updateOnTick(*this);
}

void Game::updateOnKeyPress(int allegroKeycode)
{
	state_->updateOnKeyPress(*this, allegroKeycode);
		
	eventQueue_.dispatch();
}

void Game::render() const
{
	state_->render(*this);
}

void Game::centerCameraOnPlayer_()
{
	camera_.centerOn(
		(player_.getCol() + 0.5f) * Config::assetRes,
		(player_.getRow() + 0.5f) * Config::assetRes);
}

void Game::changeState_(GameStateType stateType)
{
	delete state_;

	switch (stateType)
	{
	case GameStateType::Play:
		state_ = new GameStatePlay();
		break;
	case GameStateType::Pause:
		state_ = new GameStatePause();
		break;
	case GameStateType::Loss:
		state_ = new GameStateLoss();
		break;
	}
}