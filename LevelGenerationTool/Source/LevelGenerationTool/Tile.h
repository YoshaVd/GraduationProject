#pragma once

#include "CoreMinimal.h"

enum TileState 
{
	EMPTY,
	FILLED,
	DOOR_NONE,
	DOOR_OPEN,
	DOOR_LOCKED,
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

	bool _isFilled = true;
	FColor _color = FColor::Black;
	FVector2D _coordinates;
	int _x;
	int _y;
	// TODO: states for gameplay elements on tile
};

struct LEVELGENERATIONTOOL_API Connection
{
public:
	Connection(FVector2D start, FVector2D target)
		: _start(start), _target(target) {}
	~Connection() {}

	FVector2D _start;
	FVector2D _target;
	Connection* _headConnection;
	int _cost;
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