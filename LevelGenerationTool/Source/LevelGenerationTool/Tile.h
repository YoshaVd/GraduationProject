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
	EDGE,
	PICKUP,
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
	int _x;
	int _y;
	TileState _state = NONE;
};

struct LEVELGENERATIONTOOL_API TileConnection
{
public:
	TileConnection(FVector2D pos, FVector2D parent)
		: _pos(pos), _parent(parent) {}
	~TileConnection() {}

	FVector2D _pos;
	FVector2D _parent;
};

struct LEVELGENERATIONTOOL_API Pair
{
public:
	Pair(Tile* A, Tile* B)
		: _a(A), _b(B) {}
	~Pair() {}

	Tile* _a;
	Tile* _b;
};