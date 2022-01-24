#pragma once

#include <vector>
#include "Tile.h"
#include "Key.h"
#include "ImageData.h"
#include "Enemy.h"

class Level
{
private:
	std::unordered_map<int, Tile> tiles_;
	std::unordered_map<int, Tile> doors_;
	std::unordered_map<int, Key> keys_;
	std::unordered_map<int, Tile> exits_;
	
	std::vector<Enemy> enemies_;

	ImageData imageData_;
	int numCols_;
	int numRows_;

	int playerSpawnCol_;
	int playerSpawnRow_;

	void generate_(unsigned int level);
public:
	Level(unsigned int level);

	void updateOnTick();
	void updateOnTurn(int playerCol, int playerRow, EventQueue &gameEventQueue);

	void render() const;

	void useKeyAt(int keySpatialHash);

	bool isObstacleAt(int spatialHash) const;
	bool isKeyAt(int spatialHash) const;
	bool isExitAt(int spatialHash) const;
	bool isEnemyAt(int spatialHash) const;

	int getNumCols() const;
	int getNumRows() const;
	int getPlayerSpawnCol() const;
	int getPlayerSpawnRow() const;
	
	int spatialHash(int col, int row) const;
};