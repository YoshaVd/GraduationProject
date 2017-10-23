#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"
#include "BaseGrid.h"
#include "Room.h"

using namespace std;

/*	grid class containing all the terrain and 
	gameplay information necessary for building a level*/
class LEVELGENERATIONTOOL_API LevelGrid : public BaseGrid
{
public:
	LevelGrid(const int width, const int height) : BaseGrid(width, height) {}
	LevelGrid(vector<vector<Tile*>>& tiles) : BaseGrid(tiles) {}
	LevelGrid(const LevelGrid& other);
	~LevelGrid() {}
 
	// Subgrid functions
	void AddChild(LevelGrid* grid);
	void SetParent(LevelGrid* grid);
	LevelGrid* GetParentDeep();

	FVector2D ToParentCoordinates(const FVector2D pos);

	bool Split(const int sizeMin = 5);
	bool SplitDeep(const int sizeMin = 5);
	bool SplitHorizontal(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight);
	bool SplitVertical(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight);

	LevelGrid * CreateSubGrid(const int bottom, const int left, const int top, const int right);
	vector<LevelGrid*>& GetChildren() { return _childGrids; }

	// Room functions
	void AddRoom(const int inset = 0);
	void AddRoomToChildrenDeep(const int inset = 0);

	void ConnectRooms();
	void ConnectRoomsDeep();

	// Pathing functions
	vector<FVector2D> FindPath(const FVector2D start, const FVector2D target);
	int CalculateFcost(const FVector2D start,const FVector2D adj, const FVector2D target);

private:
	LevelGrid* _parentGrid;
	vector<LevelGrid*> _childGrids;
	vector<Room*> _rooms;
};
