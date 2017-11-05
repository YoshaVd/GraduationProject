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
	float pathDensity = _pickupDensity * _pickupPathSpawnRate;
	float sideRoomDensity = _pickupDensity * (1 - _pickupPathSpawnRate);
	float pickupEdgeSpawnRate = 1 - _pickupCenterSpawnRate;

	for (auto r : _rooms)
	{
		if (r->GetType() == ON_PATH)
		{
			r->PlaceEntitiesOnEdges(pathDensity * pickupEdgeSpawnRate, PICKUP, _pickupAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(pathDensity * _pickupCenterSpawnRate, PICKUP);
		}
		else
		{
			r->PlaceEntitiesOnEdges(sideRoomDensity * pickupEdgeSpawnRate, PICKUP, _pickupAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(sideRoomDensity * _pickupCenterSpawnRate, PICKUP);
		}
	}
}

void LevelFiller::FillRoomsWithEnemies()
{
	float pathDensity = _enemyDensity * _enemyPathSpawnRate;
	float sideRoomDensity = _enemyDensity * (1 - _enemyPathSpawnRate);
	float enemyEdgeSpawnRate = 1 - _enemyCenterSpawnRate;

	for (auto r : _rooms)
	{
		if (r->GetType() == ON_PATH)
		{
			r->PlaceEntitiesOnEdges(pathDensity * enemyEdgeSpawnRate, ENEMY, _enemyAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(pathDensity * _enemyCenterSpawnRate, ENEMY);
		}
		else
		{
			r->PlaceEntitiesOnEdges(sideRoomDensity * enemyEdgeSpawnRate, ENEMY, _enemyAlcoveRate, GetAlcoveFriendlyTiles(r));
			r->PlaceEntitiesInCenter(sideRoomDensity * _enemyCenterSpawnRate, ENEMY);
		}
	}
}

void LevelFiller::EmptyRooms()
{
	vector<vector<Tile*>> tiles = _pGrid->GetTiles();

	for (auto col : tiles)
	{
		for (auto t : col)
		{
			if (t->_state == PICKUP
				|| t->_state == ENEMY)
			{
				if (t->_parent->GetType() == ON_PATH)
					t->_state = ROOM_ON_PATH;
				else
					t->_state = ROOM;
				// fill alcoves
				if (_pGrid->GetFilledTiles(_pGrid->GetAdjacentTiles(t)).size() == 3)
					t->_isFilled = true;
			}
		}
	}
}
