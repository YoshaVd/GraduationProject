#pragma once

#include "CoreMinimal.h"

struct LEVELGENERATIONTOOL_API Tile
{
public:
	Tile() {}
	Tile(bool isFilled) : _isFilled(isFilled) {}
	~Tile() {}

	bool _isFilled = true;
	// TODO: self aware of position?
	// TODO: states for gameplay elements on tile
};
