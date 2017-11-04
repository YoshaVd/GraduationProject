#include "LevelGrid.h"
#include "LevelGenerationTool.h"
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <queue>
#include <map>
#include "Runtime/Core/Public/Containers/Map.h"
#include "Runtime/Core/Public/Containers/Queue.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

LevelGrid::LevelGrid(const LevelGrid & other)
	: BaseGrid(other)
{
	_parentGrid = other._parentGrid;
	_childGrids = other._childGrids;
	_oddsDoubleCorridor = other._oddsDoubleCorridor;
	_oddsWideCorridor = other._oddsWideCorridor;
}

LevelGrid & LevelGrid::operator=(const LevelGrid & other)
{
	_width = other._width;
	_height = other._height;
	_baseColor = other._baseColor;
	_tiles = other._tiles;
	_biasFactor = other._biasFactor;
	_parentGrid = other._parentGrid;
	_childGrids = other._childGrids;
	_oddsDoubleCorridor = other._oddsDoubleCorridor;
	_oddsWideCorridor = other._oddsWideCorridor;
	return *this;
}

void LevelGrid::AddChild(LevelGrid * grid)
{
	_childGrids.push_back(grid);
	grid->SetParent(this);
}

void LevelGrid::SetParent(LevelGrid * grid)
{
	_parentGrid = grid;
}

LevelGrid * LevelGrid::GetParentDeep()
{
	if (_parentGrid != nullptr)
		return _parentGrid->GetParentDeep();
	return this;
}

bool LevelGrid::Split(const int sizeMin)
{
	/*	50% chance to split vertically or horizontally
		split grid in 2, taking into account the minimum size */
	int rnd = rand() % 2;
	LevelGrid *subLeft(new LevelGrid(*this)), *subRight(new LevelGrid(*this));
	bool hasSplit = false;

	// First try to split based on the random dice roll
	if (rnd == 0)
		hasSplit = SplitHorizontal(sizeMin, *subLeft, *subRight);
	else
		hasSplit = SplitVertical(sizeMin, *subLeft, *subRight);
	// If that fails try to split in the other direction, taking into account the minimum size
	if (!hasSplit && _width / 2 >= sizeMin)
		hasSplit = SplitHorizontal(sizeMin, *subLeft, *subRight);
	else if (!hasSplit && _height / 2 >= sizeMin)
		hasSplit = SplitVertical(sizeMin, *subLeft, *subRight);

	if (!hasSplit) return false;

	AddChild(subLeft);
	AddChild(subRight);
	return true;
}

bool LevelGrid::SplitDeep(const int sizeMin, int level)
{
	// Deep split child grids if the current split was successful
	//int deviation = rand() % (_granularityDeviation + 1);
	int deviation = FMath::RandRange(1, GetParentDeep()->_granularityDeviation);

	if (Split(sizeMin + deviation))
	{
		for (auto c : _childGrids)
			c->SplitDeep(sizeMin, level++);
		return true;
	}
	
	return false;
}

bool LevelGrid::SplitHorizontal(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight)
{
	if (_width / 2 < sizeMin) {
		//UE_LOG(LogTemp, Warning, TEXT("LevelGrid::Split || Grid is not wide enough to split"));
		return false;
	}
	int x = rand() % (_width - 2 * sizeMin + 1) + sizeMin;
	// - 1 to prevent grid overlap
	subLeft = *CreateSubGrid(0, 0, _height, x - 1);
	subRight = *CreateSubGrid(0, x, _height, _width);
	return true;
}

bool LevelGrid::SplitVertical(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight)
{
	if (_height / 2 < sizeMin) {
		//UE_LOG(LogTemp, Warning, TEXT("LevelGrid::Split || Grid is not high enough to split [420 blaze it]"));
		return false;
	}

	int y = rand() % (_height - 2 * sizeMin + 1) + sizeMin;
	subLeft = *CreateSubGrid(0, 0, y - 1, _width);
	subRight = *CreateSubGrid(y, 0, _height, _width);
	return true;
}

LevelGrid * LevelGrid::CreateSubGrid(const int bottom, const int left, const int top, const int right)
{
	// Loop through all the tiles
	vector<vector<Tile*>> newTiles;
	for (size_t col = 0; col < _width; col++)
	{
		if (col >= left && col <= right)
			newTiles.push_back(vector<Tile*>());
		for (size_t row = 0; row < _height; row++)
		{
			// Add the tiles inside the specified rect to the sub-grid tileset
			if (row >= bottom && row <= top && col >= left && col <= right)
			{
				if (IsWithinBounds(FVector2D(col, row), FString("LevelGrid::CreateSubGrid")))
				{
					newTiles[col - left].push_back(_tiles[col][row]);
				}
			}
		}
	}

	return new LevelGrid(newTiles);
}

vector<LevelGrid*> LevelGrid::GetChildrenDeep()
{
	vector<LevelGrid*> children;
	// if this grid has children -> look for more children
	if (_childGrids.size() != 0)
	{
		for (auto c : _childGrids)
		{
			for (auto cc : c->GetChildrenDeep())
			{
				children.push_back(cc);
			}
		}
	}
	// else add this child
	else
		children.push_back(this);

	return children;
}

void LevelGrid::AddRoom(int inset)
{
	if (2 * inset + 4 > _width || 2 * inset + 4 > _height) {
		UE_LOG(LogTemp, Error, TEXT("LevelGrid::AddRoom || Inset is too high for this room size"));
		return;
	}
	if (GetParentDeep()->_isInsetRandomized)
		inset = rand() % ++inset;

	_rooms.push_back(new Room(GetTilesArea(inset, inset, _height - (inset + 1), _width - (inset + 1))));
}

void LevelGrid::AddRoomToChildrenDeep(const int inset)
{
	// if there are no children create a room
	if (_childGrids.size() == 0)
	{
		AddRoom(inset);
		return;
	}
	// else continue to children
	for (auto c : _childGrids)
		c->AddRoomToChildrenDeep(inset);
}

bool LevelGrid::ConnectRoomsStraight(Room * roomA, Room * roomB)
{
	if (roomA == nullptr || roomB == nullptr) {
		UE_LOG(LOG_LevelGenerator, Log, TEXT("LevelGrid::ConnectRoomsStraight || Invalid room."));
		return false;
	}

	vector<TPair<Tile*, Tile*>> closest = GetClosestStraightPairs(roomA->GetWalls(), roomB->GetWalls());

	// shuffle pairs and attempt to path them in that order
	random_shuffle(closest.begin(), closest.end());
	vector<Tile*> path;

	for (auto pair : closest)
	{
		if (FindStraightPath(pair.Key, pair.Value, path))
		{
			SetFilledTiles(path);
			SetTileStates(path, CORRIDOR);
			SetTileState(path[0], DOOR_NONE);
			SetTileState(path[path.size()-1], DOOR_NONE);
			roomA->AddConnection(roomB);
			roomB->AddConnection(roomA);
			return true;
		}
	}

	return false;
}

bool LevelGrid::ConnectRoomsStraightWide(Room * roomA, Room * roomB)
{
	vector<TPair<Tile*, Tile*>> pairs = GetClosestStraightPairs(roomA->GetWalls(), roomB->GetWalls());
	TPair<TPair<Tile*, Tile*>, TPair<Tile*, Tile*>> adjPairs;
	if (GetAdjacentPairs(pairs, adjPairs))
	{
		vector<Tile*> pathA;
		vector<Tile*> pathB;
		if (FindStraightPath(adjPairs.Key.Key, adjPairs.Key.Value, pathA)
			&& FindStraightPath(adjPairs.Value.Key, adjPairs.Value.Value, pathB))
		{
			SetFilledTiles(pathA);
			SetFilledTiles(pathB);
			SetTileStates(pathA, CORRIDOR);
			SetTileStates(pathB, CORRIDOR);
			SetTileState(pathA[0], DOOR_NONE);
			SetTileState(pathB[0], DOOR_NONE);
			SetTileState(pathA[pathA.size() - 1], DOOR_NONE);
			SetTileState(pathB[pathB.size() - 1], DOOR_NONE);
			roomA->AddConnection(roomB);
			roomB->AddConnection(roomA);
			return true;
		}
	}
	return false;
}

bool LevelGrid::ConnectRoomsBFS(Room * roomA, Room * roomB)
{
	// get wall positions
	if (!roomA || !roomB)
		return false;

	Tile* start = roomA->GetRandomWall();
	Tile* end = roomB->GetRandomWall();

	// find path
	vector<Tile*> path = FindShortestPathBFS(start->GetPosition(), end->GetPosition(), true);
	if (path.size() > 0)
	{
		SetFilledTiles(path);
		SetTileStates(path, CORRIDOR);
		SetTileState(path[0], DOOR_NONE);
		SetTileState(path[path.size() - 1], DOOR_NONE);
		roomA->AddConnection(roomB);
		roomB->AddConnection(roomA);
		return true;
	}
	return false;
}

void LevelGrid::ConnectRoomsDeep()
{
	if (_childGrids.size() == 0)
		return;
	
	for (auto c : _childGrids)
		c->ConnectRoomsDeep();

	// get child rooms on both sides
	vector<Room*> roomsLeft = _childGrids[0]->GetChildRoomsDeep();
	vector<Room*> roomsRight = _childGrids[1]->GetChildRoomsDeep();
	// get the closest pair of rooms between both sides
	TPair<Room*, Room*> closestRooms;
	if(roomsLeft.size() > 0 && roomsRight.size() > 0)
		closestRooms = GetClosestRoomPair(roomsLeft, roomsRight);

	// determine what kind of connection based on odds
	if (rand() % ODDS_BASE < GetParentDeep()->_oddsWideCorridor)
	{
		if (!ConnectRoomsStraightWide(closestRooms.Key, closestRooms.Value))
			ConnectRoomsStraight(closestRooms.Key, closestRooms.Value); // make regular connection if wide one fails
	}
	else
		ConnectRoomsStraight(closestRooms.Key, closestRooms.Value);

	// determine whether to generate double corridors or not
	if (rand() % ODDS_BASE < GetParentDeep()->_oddsDoubleCorridor)
	{
		if (rand() % ODDS_BASE < GetParentDeep()->_oddsWideCorridor)
		{
			if (!ConnectRoomsStraightWide(closestRooms.Key, closestRooms.Value))
				ConnectRoomsStraight(closestRooms.Key, closestRooms.Value); // make regular connection if wide one fails
		}
		else
			ConnectRoomsStraight(closestRooms.Key, closestRooms.Value);
	}
}

vector<Room*> LevelGrid::GetChildRoomsDeep()
{
	vector<Room*> childRooms;
	vector<LevelGrid*> childGrids;
	childGrids = GetChildrenDeep();
	for (auto grid : childGrids)
	{
		for (auto room : grid->_rooms)
			childRooms.push_back(room);
	}

	return childRooms;
}

Room* LevelGrid::GetClosestRoom(vector<Room*> rooms, Room * targetRoom)
{
	Room* closestRoom = nullptr;
	int shortestDistance = std::numeric_limits<int>::max();
	for (auto r : rooms)
	{
		FVector2D centerA = targetRoom->GetCenterPos();
		FVector2D centerB = r->GetCenterPos();
		if ((centerA - centerB).Size() < shortestDistance)
		{
			closestRoom = r;
			shortestDistance = (centerA - centerB).Size();
		}
	}
	return closestRoom;
}

Room * LevelGrid::GetFurthestRoom(vector<Room*> rooms, Room * targetRoom)
{
	Room* furthestRoom = nullptr;
	int biggestDistance = 0;
	vector<Tile*> path;
	for (auto r : rooms)
	{
		if (r == targetRoom)
			continue;

		path = FindShortestPathBFS(r->GetCenterPos(), targetRoom->GetCenterPos(), false);
		if (path.size() > biggestDistance)
		{
			furthestRoom = r;
			biggestDistance = path.size();
		}
	}
	return furthestRoom;
}

TPair<Room*, Room*> LevelGrid::GetClosestRoomPair(vector<Room*> roomsA, vector<Room*> roomsB)
{
	TPair<Room*, Room*> closestPair;
	int shortestDistance = std::numeric_limits<int>::max();

	for (auto a : roomsA)
	{
		Room* closestRoom = GetClosestRoom(roomsB, a);
		int distance = GetShortestDistanceStraight(a->GetWalls(), closestRoom->GetWalls());
		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			closestPair.Key = a;
			closestPair.Value = closestRoom;
		}
	}

	return closestPair;
}

vector<TPair<Tile*, Tile*>> LevelGrid::GetClosestStraightPairs(vector<Tile*> setA, vector<Tile*> setB)
{
	int closestDistance = GetShortestDistanceStraight(setA, setB);
	vector<TPair<Tile*, Tile*>> closestPairs{};
	LevelGrid* parentDeep = GetParentDeep();
	for (auto a : setA)
	{
		if (!a->_isFilled) continue; // only return filled pairs
		if (parentDeep->GetEmpties(parentDeep->GetAdjacentPositions(a->_x, a->_y)).size() > 1)
			continue;

		for (auto b : setB)
		{
			if (!b->_isFilled) continue;
			if (parentDeep->GetEmpties(parentDeep->GetAdjacentPositions(b->_x, b->_y)).size() > 1)
				continue;

			if (a->_x == b->_x || a->_y == b->_y)
			{
				int distance = (a->GetPosition() - b->GetPosition()).Size();
				if (distance == closestDistance)
					closestPairs.push_back(TPair<Tile*, Tile*>(a, b));
			}
		}
	}
	if (closestPairs.size() == 0)
		UE_LOG(LogTemp, Warning, TEXT("BaseGrid::GetClosestStraightPair || No straight pair found."));

	return closestPairs;
}

void LevelGrid::FlagRoomsOnPath(vector<Tile*> path, RoomType type)
{
	Tile* previous = path.front();
	// flag first room
	previous->_parent->FlagRoom(type);
	
	// flag the other rooms on path
	for (auto t : path)
	{
		if ((t->_state == PATH || t->_state == ROOM) &&
			(previous->_state == DOOR_NONE || previous->_state == DOOR_LOCKED || previous->_state == DOOR_OPEN))
		{
			if (t->_parent)
				t->_parent->FlagRoom(type);
		}
		previous = t;
	}
}

vector<Room*> LevelGrid::GetRoomPathToType(Room * start, RoomType type)
{
	TQueue<Room*> nodeQueue;
	vector<Room*> explored;
	TMap<Room*, Room*> connections;
	nodeQueue.Enqueue(start);

	while (!nodeQueue.IsEmpty())
	{
		Room* current;
		nodeQueue.Dequeue(current);
		if (current->GetType() == type)
		{
			vector<Room*> path;
			while (connections[current] != start)
			{
				current = connections[current];
				path.push_back(current);
			}
			return path;
		}

		vector<Room*> adjacents = current->GetConnectedRooms();

		for (auto node : adjacents)
		{
			// make sure no explored nodes are checked again
			if (std::find(explored.begin(), explored.end(), node) != explored.end())
				continue;

			// mark node as explored
			explored.push_back(node);
			// store reference to previous node
			connections.Add(node, current);
			// add to queue of nodes to examine
			nodeQueue.Enqueue(node);
		}
	}

	return vector<Room*>();
}

void LevelGrid::SetRoomDepths()
{
	for (auto r : GetChildRoomsDeep())
	{
		if (r->GetType() != ON_PATH)
		{
			int depth = GetRoomPathToType(r, ON_PATH).size() + 1;
			r->SetDepthLevel(depth);
		}
	}
}

bool LevelGrid::FindStraightPath(Tile* start, Tile* target, vector<Tile*>& path)
{
	path.clear();
	int direction = 1;
	path.push_back(start);
	LevelGrid* superParent = GetParentDeep();
	if (start->_x == target->_x) // if at same width -> vertical path
	{
		if (start->_y > target->_y) // determine whether path goes up or down
			direction = -1;

		Tile* newTile = nullptr;
		int distance = abs(start->_y - target->_y);
		for (size_t i = 0; i < distance; i++)
		{
			newTile = superParent->GetVertTile(start, i * direction);
			if (!newTile->_isFilled) 
				return false; 
			path.push_back(newTile);
		}
	}

	else if (start->_y == target->_y) // if at same height -> horizontal path
	{
		if (start->_x > target->_x) // determine whether path goes left or right
			direction = -1;

		Tile* newTile = nullptr;
		int distance = abs(start->_x - target->_x);
		for (size_t i = 0; i < distance; i++)
		{
			newTile = superParent->GetHorTile(start, i * direction);
			if (!newTile->_isFilled)
				return false;
			path.push_back(newTile);
		}
	}
	else
	{
		UE_LOG(LOG_LevelGenerator, Log, TEXT("LevelGrid::StraightPath || No straight path can be formed."));
		return false;
	}
	path.push_back(target);
	return true;
}

vector<Tile*> LevelGrid::FindShortestPathBFS(const FVector2D start, const FVector2D goal, const bool onFilledTiles)
{
	TQueue<FVector2D> nodeQueue;
	vector<FVector2D> explored;
	TMap<FVector2D, FVector2D> connections;
	nodeQueue.Enqueue(start);

	while (!nodeQueue.IsEmpty())
	{
		FVector2D current;
		nodeQueue.Dequeue(current);
		if (current == goal)
		{
			vector<Tile*> path;
			while (connections[current] != start)
			{
				current = connections[current];
				path.push_back(GetParentDeep()->_tiles[current.X][current.Y]);
			}
			return path;
		}

		vector<FVector2D> adjacents = GetAdjacentPositions(current);
		if (onFilledTiles)
			adjacents = GetFilleds(adjacents);
		else
			adjacents = GetEmpties(adjacents);

		for (FVector2D node : adjacents)
		{
			// make sure no explored nodes are checked again
			if (std::find(explored.begin(), explored.end(), node) != explored.end())
				continue;

			// mark node as explored
			explored.push_back(node);
			// store reference to previous node
			connections.Add(node, current);
			// add to queue of nodes to examine
			nodeQueue.Enqueue(node);
		}
			
	}

	return vector<Tile*>();
}