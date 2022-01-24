#pragma once

class Level;
class EventQueue;

#include <stack>
#include "Entity.h"

class Enemy : public Entity
{
private:
	struct Node
	{
		Node *parent;
		int col;
		int row;
		int f;
		int g;
		int h;

		Node(Node *parent, int col, int row) :
			parent(parent),
			col(col),
			row(row),
			f(0),
			g(0),
			h(0)
		{}
	};

	struct NodeCmp
	{
		bool operator()(const Node *lhs, const Node *rhs) const
		{
			return lhs->f > rhs->f;
		}
	};

	std::stack<std::pair<int, int>> aStarSearch_(int playerCol, int playerRow, const Level &level) const;
	std::stack<std::pair<int, int>> buildPath_(Node *end) const;
public:
	Enemy( int col, int row, const char *animationSheetPath);

	void updateOnTurn(int playerCol, int playerRow, const Level &level, EventQueue &gameEventQueue);
};