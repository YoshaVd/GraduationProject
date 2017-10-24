#include "LevelGrid.h"
#include "LevelGenerationTool.h"
#include <algorithm>
#include <stack>

LevelGrid::LevelGrid(const LevelGrid & other)
	: BaseGrid(other)
{
	_parentGrid = other._parentGrid;
	_childGrids = other._childGrids;
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

FVector2D LevelGrid::ToParentCoordinates(const FVector2D pos)
{
	auto parentTiles = _parentGrid->GetTiles();

	for (size_t col = 0; col < _parentGrid->GetWidth(); col++)
	{
		for (size_t row = 0; row < _parentGrid->GetHeight(); row++)
		{
			if (parentTiles[col][row] == _tiles[pos.X][pos.Y])
				return FVector2D(col, row);
		}
	}
	return FVector2D();
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

bool LevelGrid::SplitDeep(const int sizeMin)
{
	// Deep split child grids if the current split was successful
	if (Split(sizeMin))
	{
		for (auto c : _childGrids)
			c->SplitDeep(sizeMin);
		return true;
	}
	return false;
}

bool LevelGrid::SplitHorizontal(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight)
{
	if (_width / 2 < sizeMin) {
		UE_LOG(LogTemp, Warning, TEXT("LevelGrid::Split || Grid is not wide enough to split"));
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
		UE_LOG(LogTemp, Warning, TEXT("LevelGrid::Split || Grid is not high enough to split [420 blaze it]"));
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

void LevelGrid::AddRoom(const int inset)
{
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

void LevelGrid::ConnectRooms()
{
	vector<Room*> rooms;
	for (auto c : _childGrids)
	{
		for (auto r : c->_rooms)
			rooms.push_back(r);
	}
	for (size_t i = 0; i < rooms.size(); i += 2)
	{
		FVector2D start = FVector2D(rooms[i]->GetRandomWall()->_x, rooms[i]->GetRandomWall()->_y);
		FVector2D target = FVector2D(rooms[i + 1]->GetRandomWall()->_x, rooms[i + 1]->GetRandomWall()->_y);
		vector<FVector2D> path = FindPath(start, target);
		for (auto p : path)
		{
			SetFilled(p, false);
		}
	}
}

void LevelGrid::ConnectRoomsStraight()
{
	vector<Room*> rooms;
	for (auto c : _childGrids)
	{
		for (auto r : c->_rooms)
			rooms.push_back(r);
	}

	if (rooms.size() < 2)
		return;

	for (size_t i = 0; i < rooms.size(); i += 2)
	{
		Pair* closest = GetClosestStraightPair(rooms[0 + i]->GetWalls(), rooms[1 + i]->GetWalls());
		if (closest == nullptr)
			continue;

		auto path = StraightPath(closest->_a, closest->_b);
		SetFilledTiles(path);
	}
}

void LevelGrid::ConnectRoomsDeep()
{
	// if there are no children create a path
	if (_childGrids.size() > 0)
	{
		if (_childGrids[0]->_rooms.size() > 0)
		{
			ConnectRoomsStraight();
			return;
		}
	}
	// else continue to children
	for (auto c : _childGrids)
		c->ConnectRoomsDeep();
}

vector<Tile*> LevelGrid::StraightPath(Tile* start, Tile* target)
{
	vector<Tile*> path;
	int direction = 1;
	path.push_back(start);
	LevelGrid* superParent = GetParentDeep();
	if (start->_x == target->_x)
	{
		if (start->_y > target->_y)
			direction = -1;

		int distance = abs(start->_y - target->_y);
		for (size_t i = 0; i < distance; i++)
		{
			path.push_back(superParent->GetVertTile(start, i * direction));
		}
	}
	else if (start->_y == target->_y)
	{
		if (start->_x > target->_x)
			direction = -1;

		int distance = abs(start->_x - target->_x);
		for (size_t i = 0; i < distance; i++)
		{
			path.push_back(superParent->GetHorTile(start, i * direction));
		}
	}
	else
	{
		UE_LOG(LOG_LevelGenerator, Log, TEXT("LevelGrid::StraightPath || No straight path can be formed."));
		return vector<Tile*>();
	}
	path.push_back(target);
	return path;
}

vector<FVector2D> LevelGrid::FindPath(const FVector2D start, const FVector2D target)
{
	//vector<Connection*> openList;
	//vector<Connection*> closedList;
	//Connection* currentConnection;

	//// Initial nodes
	//for (auto c : GetConnections(start)) {
	//	c->_cost = CalculateFcost(start, c->_target, target);
	//	openList.push_back(c);
	//}

	//while (openList.size() != 0)
	//{
	//	// Get tile with lowest F cost
	//	int lowestF = std::numeric_limits<int>::max();
	//	for (auto i : isolatedAdjTiles)
	//	{
	//		int cost = CalculateFcost(start, i, target);
	//		if (cost <= lowestF) 
	//		{
	//			if (cost == lowestF && rand() % 2 == 1)
	//				continue;
	//			lowestF = cost;
	//			current = i;
	//		}
	//	}
	//}

	//stack<FVector2D> visited;
	//FVector2D current = start;
	//if (!IsWithinBounds(current, "ALevelGenerator::FindPath"))
	//	return vector<FVector2D>();

	//visited.push(current);

	//// continue looking for options as long as the stack is not empty
	//while (!visited.empty())
	//{
	//	// check for isolated adjacent tiles
	//	vector<FVector2D> adjacentTiles = GetEmptyAdjacentPositions(current);
	//	vector<FVector2D> isolatedAdjTiles = GetIsolatedPositionsExclusion(adjacentTiles, current);
	//	// if there are none, pop the stack and try the next one
	//	while (isolatedAdjTiles.size() == 0 && !visited.empty())
	//	{
	//		visited.pop();
	//		if (visited.empty())
	//			break;

	//		current = visited.top();
	//		adjacentTiles = GetEmptyAdjacentPositions(current);
	//		isolatedAdjTiles = GetIsolatedPositionsExclusion(adjacentTiles, current);
	//	}
	//	if (visited.empty())
	//		break;

	//	// Get tile with lowest F cost
	//	int lowestF = std::numeric_limits<int>::max();
	//	for (auto i : isolatedAdjTiles)
	//	{
	//		int cost = CalculateFcost(start, i, target);
	//		if (cost <= lowestF) 
	//		{
	//			if (cost == lowestF && rand() % 2 == 1)
	//				continue;
	//			lowestF = cost;
	//			current = i;
	//		}
	//	}

	//	visited.push(current);
	//	if (current == target)
	//		break;
	//}

	//// Reconstruct path
	//vector<FVector2D> path;
	//while (!visited.empty())
	//{
	//	path.push_back(current);
	//	current = visited.top();
	//	visited.pop();
	//}
	//return path;

	return vector<FVector2D>();
}

int LevelGrid::CalculateFcost(const FVector2D start, const FVector2D adj, const FVector2D target)
{
	int gCost = abs(start.X - adj.X) + abs(start.Y - adj.Y);
	int hCost = abs(target.X - adj.X) + abs(target.Y - adj.Y);
	return gCost + hCost * 10;
}

vector<Connection*> LevelGrid::GetConnections(FVector2D pos)
{
	vector<Connection*> cons;
	for (auto a : GetAdjacentPositions(pos))
	{
		cons.push_back(new Connection(pos, a));
	}
	return cons;
}
