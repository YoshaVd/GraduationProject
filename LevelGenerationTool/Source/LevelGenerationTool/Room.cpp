#include "Room.h"
#include <stack>

Room::Room(vector<vector<Tile*>> tiles) 
	: BaseGrid(tiles)
{
	SetFilledArea(1, 1, _height - 2, _width - 2);
	SetTileStatesArea(1, 1, _height - 2, _width - 2, ROOM);
	_baseColor = FColor::Blue;
	SetColorAll(_baseColor);
}

Room::Room(const Room & other) 
	: BaseGrid(other)
{
	SetFilledArea(1, 1, _height - 2, _width - 2);
	SetTileStatesArea(1, 1, _height - 2, _width - 2, ROOM);
	_baseColor = FColor::Blue;
	SetColorAll(_baseColor);
}

Tile* Room::GetRandomWall()
{
	vector<Tile*> walls = GetWalls();
	return GetRandomTileFromSet(walls);
}

vector<Tile*> Room::GetWalls()
{
	vector<Tile*> walls;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			// don't return corners
			if(IsCorner(col, row))
				continue;
			if (col == 0 || col == _width - 1 || row == 0 || row == _height - 1)
				walls.push_back(_tiles[col][row]);
		}
	}

	return walls;
}

vector<FVector2D> Room::GetWallPositions()
{
	vector<FVector2D> walls;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			// don't return corners
			if (IsCorner(col, row))
				continue;
			if (col == 0 || col == _width - 1 || row == 0 || row == _height - 1)
				walls.push_back(FVector2D(col,row));
		}
	}

	return walls;
}

vector<Tile*> Room::GetEdges()
{
	vector<Tile*> edges;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (col != 0 && col != _width - 1 && row != 0 && row != _height - 1)
				if (col == 1 || col == _width - 2 || row == 1 || row == _height - 2)
					if (!IsAdjTileWithState(FVector2D(col, row), DOOR_NONE))
						edges.push_back(_tiles[col][row]);
		}
	}

	return edges;
}

void Room::PlaceEntitiesOnEdges(vector<Entity*> entities)
{
	vector<Tile*> emptyEdges = GetTilesWithState(GetEdges(), ROOM);
	if (emptyEdges.size() < entities.size()) {
		UE_LOG(LogTemp, Error, TEXT("Room::PlaceOnEdges || More entities than empty tiles to put them on"));
		return;
	}

	for (auto entity : entities)
	{
		int randomNr;
		do
		{
			randomNr = rand() % emptyEdges.size();

		} while (!emptyEdges[randomNr]->_state == ROOM);

		emptyEdges[randomNr]->_state = PICKUP;
		
	}
}

void Room::AddAlcove(Entity * entity)
{
	vector<FVector2D> walls = GetWallPositions();

	int randomWall = 0;
	do
	{
		randomWall = rand() % walls.size();
	} while (IsNearTileWithState(walls[randomWall], DOOR_NONE)
		|| IsNearTileWithState(walls[randomWall], PICKUP)
		|| _tiles[walls[randomWall].X][walls[randomWall].Y]->_state == DOOR_NONE);

	_tiles[walls[randomWall].X][walls[randomWall].Y]->_state = PICKUP;
	_tiles[walls[randomWall].X][walls[randomWall].Y]->_isFilled = false;
}

Tile * Room::GetCenterTile()
{
	if (_tiles[_width / 2][_height / 2])
		return _tiles[_width / 2][_height / 2];
	else
	{
		for (size_t col = 0; col < _width; col++)
		{
			for (size_t row = 0; row < _height; row++)
			{
				if (!_tiles[col][row]->_isFilled)
					return _tiles[col][row];
			}
		}
	}

	return nullptr;
}

FVector2D Room::GetCenterPos()
{
	if (_tiles[_width / 2][_height / 2])
		return _tiles[_width / 2][_height / 2]->GetPosition();
	else
	{
		for (size_t col = 0; col < _width; col++)
		{
			for (size_t row = 0; row < _height; row++)
			{
				if (!_tiles[col][row]->_isFilled)
					return _tiles[col][row]->GetPosition();
			}
		}
	}
	return FVector2D(1, 1);
}

bool Room::IsCorner(const int x, const int y)
{
	return (x == 0 && y == 0) || (x == 0 && y == _height - 1) ||
		(x == _width - 1 && y == _height - 1) || (x == _width - 1 && y == 0);
}

int Room::GetShortestDistance(Room * other, int& distance)
{
	distance++;
	stack<int> distances;
	for (auto r : _connectedRooms)
	{
		if (r == other)
			distances.push(distance);
		distances.push(r->GetShortestDistance(other, distance));
	}

	int shortestDistance = std::numeric_limits<int>::max();
	while (!distances.empty())
	{
		if (distances.top() < shortestDistance)
			shortestDistance = distances.top();
		distances.pop();
	}

	return shortestDistance;
}

void Room::AddLevelStart()
{
	GetCenterTile()->_state = START_POS;
}

void Room::AddLevelEnd()
{
	GetCenterTile()->_state = END_POS;
}
