#include <random>
#include <set>
#include <string>
#include <fstream>
#include <allegro5/bitmap_io.h>
#include "Level.h"
#include "Config.h"

Level::Level(unsigned int level) :
	tiles_(),
	doors_(),
	keys_(),
	exits_(),
	enemies_({}),
	imageData_(),
	numCols_(0),
	numRows_(0)
{
	this->generate_(level);
}

void Level::updateOnTick()
{
	for(Enemy &enemy : enemies_)
		enemy.updateOnTick();
}

void Level::updateOnTurn(int playerCol, int playerRow, EventQueue &gameEventQueue)
{
	for (Enemy &enemy : enemies_)
		enemy.updateOnTurn(playerCol, playerRow, *this, gameEventQueue);
}

void Level::render() const
{
	for (auto it = tiles_.cbegin(); it != tiles_.cend(); ++it)
		it->second.render(imageData_);

	for (auto it = doors_.cbegin(); it != doors_.cend(); ++it)
		it->second.render(imageData_);

	for (auto it = keys_.cbegin(); it != keys_.cend(); ++it)
		it->second.render(imageData_);

	for (auto it = exits_.cbegin(); it != exits_.cend(); ++it)
		it->second.render(imageData_);

	for (const Enemy &enemy : enemies_)
		enemy.render();
}

void Level::useKeyAt(int keySpatialHash)
{
	doors_.erase(keys_.find(keySpatialHash)->second.doorSpatialHash());
	keys_.erase(keySpatialHash);
}

bool Level::isObstacleAt(int spatialHash) const
{
	return tiles_.find(spatialHash) != tiles_.cend()
		|| doors_.find(spatialHash) != doors_.cend();
}

bool Level::isKeyAt(int spatialHash) const
{
	return keys_.find(spatialHash) != keys_.cend();
}

bool Level::isExitAt(int spatialHash) const
{
	return exits_.find(spatialHash) != exits_.cend();
}

bool Level::isEnemyAt(int spatialHash) const
{
	for (const Enemy &enemy : enemies_)
		if (this->spatialHash(enemy.getCol(), enemy.getRow()) == spatialHash)
			return true;
	return false;
}

int Level::getNumCols() const
{
	return numCols_;
}

int Level::getNumRows() const
{
	return numRows_;
}

int Level::getPlayerSpawnCol() const
{
	return playerSpawnCol_;
}

int Level::getPlayerSpawnRow() const
{
	return playerSpawnRow_;
}

int Level::spatialHash(int col, int row) const
{
	return col + row * numCols_;
}

void Level::generate_(unsigned int level)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<int> roomTypeDis(3, 7);

	std::string sheetTilesPath = "";

	int roomSize = 0;

	std::ifstream in;

	in.open("data/1.txt");
	if(!in.is_open())
		throw std::invalid_argument("Failed to open level data");

	in >> roomSize >> sheetTilesPath;

	in.close();

	ALLEGRO_BITMAP *sheetTiles = al_load_bitmap(sheetTilesPath.c_str());
	if (!sheetTiles)
		throw std::invalid_argument("Failed to load tile sheet bitmap");

	imageData_.emplace(1, Image(sheetTiles, 0, 0, Config::assetRes, Config::assetRes));
	imageData_.emplace(2, Image(sheetTiles, 8, 0, Config::assetRes, Config::assetRes));
	imageData_.emplace(3, Image(sheetTiles, 16, 0, Config::assetRes, Config::assetRes));
	imageData_.emplace(4, Image(sheetTiles, 24, 0, Config::assetRes, Config::assetRes));
	imageData_.emplace(5, Image(sheetTiles, 0, 8, Config::assetRes, Config::assetRes));
	imageData_.emplace(6, Image(sheetTiles, 8, 8, Config::assetRes, Config::assetRes));
	imageData_.emplace(7, Image(sheetTiles, 16, 8, Config::assetRes, Config::assetRes));
	imageData_.emplace(8, Image(sheetTiles, 24, 8, Config::assetRes, Config::assetRes));

	int numRooms = std::min<unsigned int>(20, 5 + (level - 1) * 2);

	numCols_ = numRooms * (roomSize + 1) + 1;
	numRows_ = numRooms * (roomSize + 1) + 1;

	std::vector<std::vector<int>> roomTypeGrid(numRooms, std::vector<int>(numRooms, 0));
	std::set<std::pair<int, int>> availableCoords;
	std::set<std::pair<int, int>> keySpawnCoords;
	std::set<std::pair<int, int>> enemySpawnCoords;

	int redDoorSpatialHash = 0;
	int greenDoorSpatialHash = 0;
	int blueDoorSpatialHash = 0;

	int spawnRoomCol = numRooms * 0.5f;
	int spawnRoomRow = numRooms * 0.5f;

	roomTypeGrid[spawnRoomRow][spawnRoomCol] = 1;

	playerSpawnCol_ = (spawnRoomCol + 0.5f) * (roomSize + 1);
	playerSpawnRow_ = (spawnRoomRow + 0.5f) * (roomSize + 1);

	availableCoords.emplace(spawnRoomCol - 1, spawnRoomRow);
	availableCoords.emplace(spawnRoomCol + 1, spawnRoomRow);
	availableCoords.emplace(spawnRoomCol, spawnRoomRow - 1);
	availableCoords.emplace(spawnRoomCol, spawnRoomRow + 1);

	for (int i = 0; i < numRooms; ++i)
	{	
		auto it = availableCoords.cbegin();
		std::advance(it, std::uniform_int_distribution<size_t>(0, availableCoords.size() - 1)(eng));
		
		const std::pair<int, int> &coords = *it;

		roomTypeGrid[coords.second][coords.first] = roomTypeDis(eng);

		if (coords.first > 0 && roomTypeGrid[coords.second][coords.first - 1] == 0)
			availableCoords.emplace(coords.first - 1, coords.second);

		if (coords.first < numRooms - 1 && roomTypeGrid[coords.second][coords.first + 1] == 0)
			availableCoords.emplace(coords.first + 1, coords.second);

		if (coords.second > 0 && roomTypeGrid[coords.second - 1][coords.first] == 0)
			availableCoords.emplace(coords.first, coords.second - 1);

		if (coords.second < numRooms - 1 && roomTypeGrid[coords.second + 1][coords.first] == 0)
			availableCoords.emplace(coords.first, coords.second + 1);

		availableCoords.erase(it);
	}

	auto it = availableCoords.cbegin();
	std::advance(it, std::uniform_int_distribution<size_t>(0, availableCoords.size() - 1)(eng));
	const std::pair<unsigned int, unsigned int> &coords = *it;
	roomTypeGrid[coords.second][coords.first] = 2;
	availableCoords.erase(it);

	for (int roomRow = 0; roomRow < numRooms; ++roomRow)
	{
		for (int roomCol = 0; roomCol < numRooms; ++roomCol)
		{
			if (roomTypeGrid[roomRow][roomCol] != 0)
			{
				int tileCol = roomCol * (roomSize + 1) + 1;
				int tileRow = roomRow * (roomSize + 1) + 1;

				if (roomRow == 0 || roomTypeGrid[roomRow - 1][roomCol] == 0)
				{
					if(tiles_.find(this->spatialHash(tileCol - 1, tileRow - 1)) == tiles_.cend())
						tiles_.emplace(this->spatialHash(tileCol - 1, tileRow - 1), Tile(tileCol - 1, tileRow - 1, 1));
					if(tiles_.find(this->spatialHash(tileCol + roomSize, tileRow - 1)) == tiles_.cend())
						tiles_.emplace(this->spatialHash(tileCol + roomSize, tileRow - 1), Tile(tileCol + roomSize, tileRow - 1, 1));

					for (int col = tileCol; col < tileCol + roomSize; ++col)
						tiles_.emplace(this->spatialHash(col, tileRow - 1), Tile(col, tileRow - 1, 1));
				}

				if(tiles_.find(this->spatialHash(tileCol - 1, tileRow + roomSize)) == tiles_.cend())
					tiles_.emplace(this->spatialHash(tileCol - 1, tileRow + roomSize), Tile(tileCol - 1, tileRow + roomSize, 1));
				if(tiles_.find(this->spatialHash(tileCol + roomSize, tileRow + roomSize)) == tiles_.cend())
					tiles_.emplace(this->spatialHash(tileCol + roomSize, tileRow + roomSize), Tile(tileCol + roomSize, tileRow + roomSize, 1));
				if (roomRow == numRooms - 1 || roomTypeGrid[roomRow + 1][roomCol] == 0)
				{
					for (int col = tileCol; col < tileCol + roomSize; ++col)
						tiles_.emplace(this->spatialHash(col, tileRow + roomSize), Tile(col, tileRow + roomSize, 1));
				}
				else
				{
					for (int col = tileCol; col < tileCol + roomSize * 0.5f - 1; ++col)
						tiles_.emplace(this->spatialHash(col, tileRow + roomSize), Tile(col, tileRow + roomSize, 1));

					for (int col = tileCol + roomSize * 0.5f + 1; col < tileCol + roomSize; ++col)
						tiles_.emplace(this->spatialHash(col, tileRow + roomSize), Tile(col, tileRow + roomSize, 1));
				}

				if (roomCol == 0 || roomTypeGrid[roomRow][roomCol - 1] == 0)
				{
					for (int row = tileRow; row < tileRow + roomSize; ++row)
						tiles_.emplace(this->spatialHash(tileCol - 1, row), Tile(tileCol - 1, row, 1));
				}

				if (roomCol == numRooms - 1 || roomTypeGrid[roomRow][roomCol + 1] == 0)
				{
					for (int row = tileRow; row < tileRow + roomSize; ++row)
						tiles_.emplace(this->spatialHash(tileCol + roomSize, row), Tile(tileCol + roomSize, row, 1));
				}
				else
				{
					for (int row = tileRow; row < tileRow + roomSize * 0.5f - 1; ++row)
						tiles_.emplace(this->spatialHash(tileCol + roomSize, row), Tile(tileCol + roomSize, row, 1));

					for (int row = tileRow + roomSize * 0.5f + 1; row < tileRow + roomSize; ++row)
						tiles_.emplace(this->spatialHash(tileCol + roomSize, row), Tile(tileCol + roomSize, row, 1));
				}

				std::string dataPath = "data/1_" + std::to_string(roomTypeGrid[roomRow][roomCol]) + ".txt";
				unsigned int input = 0;

				in.open(dataPath);
				if (!in.is_open())
					throw std::invalid_argument("Failed to open room data");

				for (int row = tileRow; row < tileRow + roomSize; ++row)
				{
					for (int col = tileCol; col < tileCol + roomSize; ++col)
					{
						in >> input;

						switch (input)
						{
						case 0:
							break;
						case 1:
							//obstacle
							tiles_.emplace(this->spatialHash(col, row), Tile(col, row, 1));
							break;
						case 2:
							//possible key spawn
							keySpawnCoords.emplace(col, row);
							break;
						case 3:
							//possible enemy spawn
							enemySpawnCoords.emplace(col, row);
							break;
						case 4:
							redDoorSpatialHash = this->spatialHash(col, row);
							doors_.emplace(redDoorSpatialHash, Tile(col, row, 2));
							break;
						case 5:
							greenDoorSpatialHash = this->spatialHash(col, row);
							doors_.emplace(greenDoorSpatialHash, Tile(col, row, 3));
							break;
						case 6:
							blueDoorSpatialHash = this->spatialHash(col, row);
							doors_.emplace(blueDoorSpatialHash, Tile(col, row, 4));
							break;
						case 7:
							exits_.emplace(this->spatialHash(col, row), Tile(col, row, 5));
							break;
						}
					}
					in.clear();
					in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}

				in.close();
			}
		}
	}

	//red key
	it = keySpawnCoords.cbegin();
	std::advance(it, std::uniform_int_distribution<size_t>(0, keySpawnCoords.size() - 1)(eng));
	keys_.emplace(this->spatialHash(it->first, it->second), Key(it->first, it->second, 6, redDoorSpatialHash));
	keySpawnCoords.erase(it);

	//green key
	it = keySpawnCoords.cbegin();
	std::advance(it, std::uniform_int_distribution<size_t>(0, keySpawnCoords.size() - 1)(eng));
	keys_.emplace(this->spatialHash(it->first, it->second), Key(it->first, it->second, 7, greenDoorSpatialHash));
	keySpawnCoords.erase(it);

	//blue key
	it = keySpawnCoords.cbegin();
	std::advance(it, std::uniform_int_distribution<size_t>(0, keySpawnCoords.size() - 1)(eng));
	keys_.emplace(this->spatialHash(it->first, it->second), Key(it->first, it->second, 8, blueDoorSpatialHash));
	keySpawnCoords.erase(it);

	//enemies
	unsigned int numEnemies = numRooms / 3;
	for (unsigned int i = 0; i < numEnemies; ++i)
	{
		auto it = enemySpawnCoords.cbegin();
		std::advance(it, std::uniform_int_distribution<size_t>(0, enemySpawnCoords.size() - 1)(eng));
		enemies_.push_back(Enemy(it->first, it->second, "img/sheet-enemy-8.png"));
		enemySpawnCoords.erase(it);
	}
}