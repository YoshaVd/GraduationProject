#include "LevelFiller.h"

LevelFiller::~LevelFiller()
{
}

vector<Tile*> LevelFiller::GetAlcoveFriendlyTiles(Room * room)
{
	vector<Tile*> walls = room->GetWalls();
	vector<Tile*> empties{};
	vector<Tile*> alcoves{};

	for (auto w : walls)
	{
		// check if the empty adjacent tiles are in the same room
		// if they are not an unwanted connection to another room is being made -> remove that tile
		empties = _pGrid->GetEmptyTiles(_pGrid->GetAdjacentTiles(w));
		if (empties.size() >= 1)
		{
			if (_pGrid->GetTilesWithState(empties, DOOR_NONE).size() != 0
				|| _pGrid->GetTilesWithState(empties, DOOR_OPEN).size() != 0
				|| _pGrid->GetTilesWithState(empties, DOOR_LOCKED).size() != 0)
				continue;
			if (empties.size() > 2) {
				if (w->_parent != empties[2]->_parent)
					continue;
			}
			if (empties.size() > 1) {
				if (w->_parent != empties[1]->_parent)
					continue;
			}
			if (w->_parent != empties[0]->_parent)
				continue;

			alcoves.push_back(w);
		}
	}

	return alcoves;
}

void LevelFiller::FillRoomsWithLoot()
{
	float pickupEdgeSpawnRate = 1 - _pickupCenterSpawnRate;
	float pathDensity = _pickupDensity * _pickupPathSpawnRate;
	float sideDesnity = _pickupDensity *_pickupSideSpawnRate;

	for (auto r : _rooms)
	{
		if (r->GetType() == ON_PATH || r->GetType() == START)
		{
			r->PlaceEntitiesOnEdges(pathDensity * pickupEdgeSpawnRate, PICKUP, _pickupAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(pathDensity * _pickupCenterSpawnRate, PICKUP);
		}
		else
		{
			r->PlaceEntitiesOnEdges(sideDesnity * pickupEdgeSpawnRate * r->GetDepthLevel() / 2, PICKUP, _pickupAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(sideDesnity * _pickupCenterSpawnRate * r->GetDepthLevel() / 2, PICKUP);
		}
	}
}

void LevelFiller::FillRoomsWithEnemies()
{
	float enemyEdgeSpawnRate = 1 - _enemyCenterSpawnRate;

	for (auto r : _rooms)
	{
		if (r->GetType() == START)
			continue;

		if (r->GetType() == ON_PATH)
		{
			r->PlaceEntitiesOnEdges(_enemyDensity * _enemyPathSpawnRate * enemyEdgeSpawnRate, ENEMY, _enemyAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(_enemyDensity * _enemyPathSpawnRate * _enemyCenterSpawnRate, ENEMY);
		}
		else
		{
			r->PlaceEntitiesOnEdges(_enemyDensity * _enemySideSpawnRate * enemyEdgeSpawnRate, ENEMY, _enemyAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(_enemyDensity * _enemySideSpawnRate * _enemyCenterSpawnRate, ENEMY);
		}
	}
}

void LevelFiller::EmptyRooms()
{
	vector<vector<Tile*>> tiles2D;
	vector<Tile*> tiles;
	vector<Tile*> entities;
	vector<TileState> states{ PICKUP, ENEMY };
	vector<Tile*> walls;
	for (auto r : _rooms)
	{
		walls = r->GetWallTiles();
		// 1d array of room tiles
		tiles2D = r->GetTiles();
		for (auto col : tiles2D)
		{
			for (auto t : col)
			{
				tiles.push_back(t);
			}
		}

		// put tiles with object back to their intended roomstate
		entities = _pGrid->GetTilesWithStates(tiles, states);
		for (auto e : entities)
		{
			if (e->_parent->GetType() == ON_PATH)
				e->_state = ROOM_ON_PATH;
			else
				e->_state = ROOM;

			// if loot == wall -> fill alcove
			for (auto w : walls) 
			{
				if (e == w)
					e->_isFilled = true;
			}
			
		}
	}
}