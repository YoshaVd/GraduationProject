#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"

class LEVELGENERATIONTOOL_API Room : public BaseGrid
{
public:
	Room(vector<vector<Tile*>> tiles);
	Room(const Room& other);
	~Room() {}

	FVector2D GetRandomWall();
	vector<FVector2D> GetWalls();

	bool IsConnectedTo(const FVector2D pos);
	bool IsConnectedTo(const Room& room);
};