#pragma once

#include "CoreMinimal.h"
class Room;

enum TileState 
{
	NONE,
	ROOM,
	ROOM_ON_PATH,
	CORRIDOR,
	START_POS,
	END_POS,
	DOOR_NONE,
	DOOR_OPEN,
	DOOR_LOCKED,
	PATH,
	PICKUP,
	ENEMY,
	KEY,
};

struct LEVELGENERATIONTOOL_API Tile
{
public:
	Tile() {}
	Tile(FVector2D coordinates) { 
		_x = coordinates.X;
		_y = coordinates.Y;
	}
	Tile(bool isFilled) : _isFilled(isFilled) {}
	~Tile() {}

	/* --- Functions --- */
	FVector2D GetPosition() { return FVector2D(_x, _y); }

	/* --- Members --- */
	bool _isFilled = true;
	FColor _color = FColor::Black;
	int _x = -1;
	int _y = -1;
	TileState _state = NONE;

	Room* _parent = nullptr;
};