#pragma once

#include "CoreMinimal.h"
#include "LevelGrid.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"

class LEVELGENERATIONTOOL_API Room : public LevelGrid
{
public:
	Room(vector<vector<Tile*>>& tiles);
	~Room() {}

	FVector2D GetRandomWall();
	vector<FVector2D> GetWalls();

	bool IsConnectedTo(const FVector2D pos);
	bool IsConnectedTo(const Room& room);
};