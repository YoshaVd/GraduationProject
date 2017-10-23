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
	Tile(bool isFilled) : _isFilled(isFilled) {}
	~Tile() {}

	bool _isFilled = true;
	FColor _color = FColor::Black;
	// TODO: self aware of position?
	// TODO: states for gameplay elements on tile
};
