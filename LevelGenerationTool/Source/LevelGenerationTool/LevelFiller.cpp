#include "LevelFiller.h"

LevelFiller::~LevelFiller()
{
}

void LevelFiller::SetStartAndEnd()
{
	// Get the last room of the binary tree and offset it by a random amount
	int endOffset = rand() % (_rooms.size() / 5);
	Room* endRoom = _rooms[_rooms.size() - (endOffset % _rooms.size() + 1)];
	endRoom->AddLevelEnd();

	// Get the furthest room from the end room
	Room* startRoom = _pGrid->GetFurthestRoom(_rooms, _rooms.back());

	// Get the room-path between start and end
	auto roomPath = _pGrid->GetRoomPath(startRoom, endRoom);

	// Move the start room closer by a random amount
	startRoom = roomPath[roomPath.size() - (rand() % (roomPath.size() / 4) + 1)];
	startRoom->AddLevelStart();

	// Set the room-path member for key/door placement
	_roomPath = _pGrid->GetRoomPath(startRoom, endRoom);
	reverse(_roomPath.begin(), _roomPath.end());

	// Flag rooms and set depths
	auto path = _pGrid->FindShortestPathBFS(startRoom->GetCenterPos(), endRoom->GetCenterPos(), false);
	_pGrid->FlagRoomsOnPath(path, ON_PATH);
	_pGrid->SetRoomDepths();

	// Display the path
	for (auto t : path)
	{
		_pGrid->SetColor(t, FColor::Yellow);
		if (t->_state == ROOM_ON_PATH || t->_state == ROOM || t->_state == DOOR_NONE)
			_pGrid->SetTileState(t, PATH);
	}
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
				|| _pGrid->GetTilesWithState(empties, DOOR_HIDDEN).size() != 0
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

void LevelFiller::AddLockedDoorAndKey()
{
	// place random locked door
	int lockedIndex = rand() % (_roomPath.size() - 1) + 1;
	_roomPath[lockedIndex]->AddLockedDoorFrom(_roomPath[lockedIndex - 1]);

	// Get all rooms before the locked door
	auto rooms = _pGrid->GetRoomsBeforeLockedDoor(_roomPath.front());
	if (rooms.empty())
		return;

	// Find side rooms
	auto sideRooms = GetSideRooms(rooms);

	UE_LOG(LogTemp, Warning, TEXT("rooms before door: %d"), rooms.size());
	UE_LOG(LogTemp, Warning, TEXT("side rooms before door: %d"), sideRooms.size());

	if (!sideRooms.empty())
	{
		int deepest = 0;
		Room* deepestRoom = nullptr;
		for (auto r : sideRooms)
		{
			if (r->GetDepthLevel() >= deepest)
			{
				deepest = r->GetDepthLevel();
				r = deepestRoom;
			}
		}
		deepestRoom = sideRooms[rand() % sideRooms.size()];
		deepestRoom->GetMiddle()[rand() % deepestRoom->GetMiddle().size()]->_state = KEY;
	}
	else if(!rooms.empty())
	{
		Room* keyRoom = _pGrid->GetFurthestRoom(rooms, _roomPath[lockedIndex]);
		keyRoom->GetMiddle()[rand() % keyRoom->GetMiddle().size()]->_state = KEY;
	}
}

void LevelFiller::AddHiddenRoom()
{
	auto sideRooms = GetSideRooms(_rooms);
	if (!sideRooms.empty())
	{
		int deepest = 0;
		Room* deepestRoom = nullptr;
		for (auto r : sideRooms)
		{
			if (r->GetDepthLevel() > deepest)
			{
				deepest = r->GetDepthLevel();
				r = deepestRoom;
			}
		}
		deepestRoom = sideRooms[rand() % sideRooms.size()];
		auto doors = deepestRoom->GetTilesWithState(deepestRoom->GetTiles1D(), DOOR_NONE);
		for (auto d : doors)
			d->_state = DOOR_HIDDEN;
	}
}

vector<Room*> LevelFiller::GetSideRooms(vector<Room*> rooms)
{
	vector<Room*> sideRooms;
	for (auto r : rooms)
	{
		if (r && r->GetType() != ON_PATH && r->GetType() != START)
			sideRooms.push_back(r);
	}
	return sideRooms;
}
