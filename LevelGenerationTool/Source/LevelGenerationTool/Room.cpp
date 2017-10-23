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

FVector2D Room::GetRandomWall()
{
	vector<FVector2D> walls = GetWalls();
	return GetRandomPosFromSet(walls);
}

vector<FVector2D> Room::GetWalls()
{
	vector<FVector2D> walls;
	for (size_t col = 0; col < _width; col++)
	{
		for (size_t row = 0; row < _height; row++)
		{
			if (row == 0 || row == _height - 1)
				walls.push_back(FVector2D(col, row));
			if (col == 0 || col == _width - 1)
				walls.push_back(FVector2D(col, row));
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
