#include <allegro5/keycodes.h>
#include "Player.h"
#include "Level.h"
#include "EventQueue.h"
#include "GameEvent.h"
#include "SoundBox.h"
#include "Config.h"

Player::Player(int col, int row, const char *animationSheetPath) :
	Entity(col, row, animationSheetPath),
	moved_(false)
{}

void Player::updateOnKeyPress(int allegroKeycode, Level &level, EventQueue &gameEventQueue)
{
	int newCol = this->getCol();
	int newRow = this->getRow();

	moved_ = false;

	switch (allegroKeycode)
	{
	case ALLEGRO_KEY_W:
	case ALLEGRO_KEY_UP:
		if (newRow > 0)
			--newRow;
		this->getAnimation_().setDirection(EntityAnimation::Direction::Up);
		break;
	case ALLEGRO_KEY_A:
	case ALLEGRO_KEY_LEFT:
		if (newCol > 0)
			--newCol;
		this->getAnimation_().setDirection(EntityAnimation::Direction::Left);
		break;
	case ALLEGRO_KEY_S:
	case ALLEGRO_KEY_DOWN:
		if (newRow < level.getNumRows() - 1)
			++newRow;
		this->getAnimation_().setDirection(EntityAnimation::Direction::Down);
		break;
	case ALLEGRO_KEY_D:
	case ALLEGRO_KEY_RIGHT:
		if (newCol < level.getNumCols() - 1)
			++newCol;
		this->getAnimation_().setDirection(EntityAnimation::Direction::Right);
		break;
	}

	if ((newCol != this->getCol() || newRow != this->getRow()))
	{
		int spatialHash = level.spatialHash(newCol, newRow);

		if (!level.isObstacleAt(spatialHash))
		{
			SoundBox::instance().playSample(3, ALLEGRO_PLAYMODE_ONCE, 1.0f);

			this->setCol_(newCol);
			this->setRow_(newRow);
			moved_ = true;

			if (level.isEnemyAt(spatialHash))
			{
				gameEventQueue.send(new EventLoss());
			}
			else if (level.isKeyAt(spatialHash))
			{
				SoundBox::instance().playSample(4, ALLEGRO_PLAYMODE_ONCE, 1.0f);
				level.useKeyAt(spatialHash);
			}
			else if (level.isExitAt(spatialHash))
			{
				gameEventQueue.send(new EventLevelComplete());
			}
		}
	}
}

void Player::setCol(int col)
{
	this->setCol_(col);
}

void Player::setRow(int row)
{
	this->setRow_(row);
}

bool Player::moved() const
{
	return moved_;
}