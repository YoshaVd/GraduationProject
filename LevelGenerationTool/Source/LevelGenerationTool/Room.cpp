#include "Room.h"

Room::Room(vector<vector<Tile*>> tiles) 
	: BaseGrid(tiles)
{
	SetFilledArea(1, 1, _height - 2, _width - 2);
	_baseColor = FColor::Blue;
	SetColorAll(_baseColor);
}

Room::Room(const Room & other) 
	: BaseGrid(other)
{
	SetFilledArea(1, 1, _height - 2, _width - 2);
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

bool Room::IsConnectedTo(const FVector2D pos)
{
	return false;
}

bool Room::IsConnectedTo(const Room & room)
{
	return false;
}

bool Room::IsCorner(const int x, const int y)
{
	return (x == 0 && y == 0) || (x == 0 && y == _height - 1) ||
		(x == _width - 1 && y == _height - 1) || (x == _width - 1 && y == 0);
}
