#include "Room.h"
#include <stack>
#include <algorithm>
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

Room::Room(vector<vector<Tile*>> tiles) 
	: BaseGrid(tiles)
{
	SetFilledArea(1, 1, _height - 2, _width - 2);
	SetTileStatesArea(1, 1, _height - 2, _width - 2, ROOM);
	SetTilesParent();

	_baseColor = FColor::Blue;
	SetColorAll(_baseColor);
}

Room::Room(const Room & other) 
	: BaseGrid(other)
{
	SetFilledArea(1, 1, _height - 2, _width - 2);
	SetTileStatesArea(1, 1, _height - 2, _width - 2, ROOM);
	SetTilesParent();

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
			if (!IsWithinBounds(col, row))
				continue;
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

vector<Tile*> Room::GetWallTiles()
{
	vector<Tile*> walls;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			// don't return corners
			if (IsCorner(col, row))
				continue;
			if (col == 0 || col == _width - 1 || row == 0 || row == _height - 1)
				walls.push_back(_tiles[col][row]);
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
					if (!IsAdjTileWithState(FVector2D(col, row), DOOR_NONE)
						&& !IsAdjTileWithState(FVector2D(col, row), DOOR_LOCKED)
						&& !IsAdjTileWithState(FVector2D(col, row), DOOR_LOCKED))
						edges.push_back(_tiles[col][row]);
		}
	}

	return edges;
}

vector<vector<Tile*>> Room::GetMiddle2D()
{
	vector<vector<Tile*>> middle;
	for (size_t col = 0; col < _width; col++)
	{
		if (col > 1 && col < _width - 2)
			middle.push_back(vector<Tile*>());
		for (size_t row = 0; row < _height; row++)
		{
			if (col > 1 && col < _width - 2 && row > 1 && row < _height - 2)
			{
				if (IsWithinBounds(FVector2D(col, row), FString("Room::GetMiddle")))
					middle[col - 2].push_back(_tiles[col][row]);
			}
		}
	}

	return middle;
}

vector<Tile*> Room::GetMiddle()
{
	vector<Tile*> middle;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (col > 1 && col < _width - 2 && row > 1 && row < _height - 2)
			{
				if (IsWithinBounds(FVector2D(col, row), FString("Room::GetMiddle")))
					middle.push_back(_tiles[col][row]);
				
			}
		}
	}

	return middle;
}

void Room::PlaceEntitiesOnEdges(float density, const TileState state, float alcoveDensity, vector<Tile*> alcoveTiles)
{
	if (!(state == PICKUP || state == ENEMY || state == KEY)) {
		UE_LOG(LogTemp, Error, TEXT("Room::PlaceEntitiesInCenter || Incorrect entity type"));
		return;
	}

	// calculate densities
	density = FMath::Clamp<float>(density, 0, 1);
	float edgeDensity = density * (1 - alcoveDensity);
	alcoveDensity = density * alcoveDensity;

	// calculate amounts based on densities
	int amount = GetMaxEdgeEntities();
	int amountEdge = amount * edgeDensity;
	int amountAlcove = amount * alcoveDensity;
	// adjust alcove amount if not enough alcoves are available
	if (amountAlcove > alcoveTiles.size())
		amountAlcove = alcoveTiles.size();


	// fill edges
	vector<TileState> states{ ROOM, ROOM_ON_PATH };
	vector<Tile*> edges = GetTilesWithStates(GetEdges(), states);
	random_shuffle(edges.begin(), edges.end());

	for (size_t i = 0; i < amountEdge; i++)
		edges[i]->_state = state;
	
	// fill alcoves
	random_shuffle(alcoveTiles.begin(), alcoveTiles.end());
	for (size_t i = 0; i < amountAlcove; i++)
	{
		if (i - 1 > alcoveTiles.size())
			continue;
		alcoveTiles[i]->_isFilled = false;
		alcoveTiles[i]->_state = state;
	}
}

void Room::PlaceEntitiesInCenter(float density, TileState state)
{
	if (!(state == PICKUP || state == ENEMY || state == KEY)) {
		UE_LOG(LogTemp, Error, TEXT("Room::PlaceEntitiesInCenter || Incorrect entity type"));
		return;
	}

	density = FMath::Clamp<float>(density, 0, 1);
	int amount = GetMaxCenterEntities() * density;

	if (state == ENEMY)
	{
		float roomSizeFactor = float(_width + _height + (_width + _height) / 2) / (_width * _height);
		roomSizeFactor = FMath::Clamp<float>(roomSizeFactor, 0.0, 1.0);
		amount *= roomSizeFactor;
	}
	
	vector<TileState> states{ ROOM, ROOM_ON_PATH };
	vector<Tile*> middle = GetMiddle();
	random_shuffle(middle.begin(), middle.end());
	for (size_t i = 0; i < amount; i++)
	{
		middle[i]->_state = state;
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
	if (IsWithinBounds(_width / 2, _height / 2))
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
	if (IsWithinBounds(_width / 2, _height / 2))
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

bool Room::Contains(TileState state)
{
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (_tiles[col][row]->_state == state)
				return true;
		}
	}
	return false;
}

void Room::SetTilesParent()
{
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			_tiles[col][row]->_parent = this;
		}
	}
}

void Room::FlagRoom(RoomType type)
{
	_type = type;
	if (type == ON_PATH)
	{
		for (auto t : _tiles)
			SetTileStates(GetTilesWithState(t, ROOM), ROOM_ON_PATH);
	}
}

void Room::AddLevelStart()
{
	GetCenterTile()->_state = START_POS;
}

void Room::AddLevelEnd()
{
	GetCenterTile()->_state = END_POS;
}

int Room::GetMaxEdgeEntities()
{
	// bases maximum amount of entities on the ratio and the amount of currently available tiles
	vector<TileState> states{ ROOM, ROOM_ON_PATH };
	return GetTilesWithStates(GetEdges(),states).size() * ENTITY_PER_EDGE;
}

int Room::GetMaxCenterEntities()
{
	// bases maximum amount of entities on the ratio and the amount of currently available tiles
	vector<TileState> states{ ROOM, ROOM_ON_PATH };
	return GetTilesWithStates(GetMiddle(), states).size() * ENTITY_PER_MIDDLE;
}
