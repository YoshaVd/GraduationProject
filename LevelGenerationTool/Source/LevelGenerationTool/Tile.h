#pragma once

#include "CoreMinimal.h"

enum TileState 
{
	NONE,
	ROOM,
	CORRIDOR,
	START_POS,
	END_POS,
	DOOR_NONE,
	DOOR_OPEN,
	DOOR_LOCKED,
	PATH,
	PICKUP,
	ENEMY,
};

struct LEVELGENERATIONTOOL_API Tile
{
public:
	Tile() {}
	Tile(FVector2D coordinates) : _coordinates(coordinates) { 
		_x = _coordinates.X;
		_y = _coordinates.Y;
	}
	Tile(bool isFilled) : _isFilled(isFilled) {}
	~Tile() {}

	FVector2D GetPosition() { return FVector2D(_x, _y); }

	bool _isFilled = true;
	FColor _color = FColor::Black;
	FVector2D _coordinates;
	int _x = -1;
	int _y = -1;
	TileState _state = NONE;
};