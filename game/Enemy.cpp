#include <queue>
#include "Enemy.h"
#include "Level.h"
#include "EventQueue.h"
#include "GameEvent.h"

Enemy::Enemy(int col, int row, const char *animationSheetPath) :
	Entity(col, row, animationSheetPath)
{}

void Enemy::updateOnTurn(int playerCol, int playerRow, const Level &level, EventQueue &gameEventQueue)
{
	//calculate path to player
	//advance position to first tile in path
	//if on player, send game over event

	std::stack<std::pair<int, int>> path = this->aStarSearch_(playerCol, playerRow, level);
	
	if (path.empty()) return;

	const std::pair<int, int> &nextPos = path.top();

	if (level.isEnemyAt(level.spatialHash(nextPos.first, nextPos.second)))
		return;

	if (nextPos.second < this->getRow())
	{
		this->getAnimation_().setDirection(EntityAnimation::Direction::Up);
	}
	else if (nextPos.first < this->getCol())
	{
		this->getAnimation_().setDirection(EntityAnimation::Direction::Left);
	}
	else if (nextPos.second > this->getRow())
	{
		this->getAnimation_().setDirection(EntityAnimation::Direction::Down);
	}
	else if (nextPos.first > this->getCol())
	{
		this->getAnimation_().setDirection(EntityAnimation::Direction::Right);
	}

	this->setCol_(nextPos.first);
	this->setRow_(nextPos.second);

	if (this->getCol() == playerCol && this->getRow() == playerRow)
	{
		//send game-over event
		gameEventQueue.send(new EventLoss());
	}
}

std::stack<std::pair<int, int>> Enemy::aStarSearch_(int playerCol, int playerRow, const Level &level) const
{
	std::priority_queue<Node *, std::vector<Node *>, NodeCmp> open;
	std::unordered_map<int, Node *> closed;

	Node *start = new Node(nullptr, this->getCol(), this->getRow());

	start->h = abs(playerCol - start->col) + abs(playerRow - start->row);
	start->f = start->g + start->h;

	open.push(start);
	closed.emplace(level.spatialHash(start->col, start->row), start);

	while (!open.empty())
	{
		Node *currentNode = open.top();

		if (currentNode->col == playerCol && currentNode->row == playerRow)
		{
			std::stack<std::pair<int, int>> path = this->buildPath_(currentNode);

			for (auto it = closed.begin(); it != closed.end(); ++it)
				delete it->second;

			return path;
		}

		open.pop();

		std::vector<std::pair<int, int>> potentials = {
			{ currentNode->col - 1, currentNode->row },
			{ currentNode->col + 1, currentNode->row },
			{ currentNode->col, currentNode->row - 1 },
			{ currentNode->col, currentNode->row + 1 },
		};

		for (const std::pair<int, int> &coords : potentials)
		{
			int hash = level.spatialHash(coords.first, coords.second);
			if (!level.isObstacleAt(hash))
			{
				int newG = currentNode->g + 1;

				auto it = closed.find(hash);
				if (it == closed.cend())
				{
					Node *nextNode = new Node(currentNode, coords.first, coords.second);

					nextNode->g = newG;
					nextNode->h = abs(playerCol - nextNode->col) + abs(playerRow - nextNode->row);
					nextNode->f = nextNode->g + nextNode->h;

					open.push(nextNode);
					closed.emplace(hash, nextNode);
				}
				else if (newG < it->second->g)
				{
					it->second->g = newG;
					it->second->f = newG + it->second->h;
					it->second->parent = currentNode;
				}
			}
		}
	}

	return {};
}

std::stack<std::pair<int, int>> Enemy::buildPath_(Node *end) const
{
	std::stack<std::pair<int, int>> result;
	Node *it = end;

	while (it->parent != nullptr)
	{
		result.push({ it->col, it->row });
		it = it->parent;
	}

	return result;
}