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

	LevelGrid * CreateSubGrid(const int bottom, const int left, const int top, const int right);
	vector<LevelGrid*>& GetChildren() { return _childGrids; }
	vector<LevelGrid*> GetChildrenDeep();

	// Binary partitioning functions
	bool Split(const int sizeMin = 5);
	bool SplitDeep(const int sizeMin = 5);
	bool SplitHorizontal(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight);
	bool SplitVertical(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight);

	// Room functions
	void AddRoom(const int inset = 0);
	void AddRoomToChildrenDeep(const int inset = 0);
	void ConnectRooms();
	void ConnectRoomsStraight(Room* roomA, Room* roomB);
	void ConnectRoomsDeep();

	vector<Room*> GetChildRoomsDeep();
	Room* GetClosestRoom(vector<Room*> rooms, Room* targetRoom);
	vector<Room*> GetClosestRoomPair(vector<Room*> roomsA, vector<Room*> roomsB);

	// Pathing functions
	vector<Tile*> StraightPath(Tile* start, Tile* target);
	vector<FVector2D> FindPath(const FVector2D start, const FVector2D target);
	int CalculateFcost(const FVector2D start,const FVector2D adj, const FVector2D target);
	vector<Connection*> GetConnections(FVector2D pos);

private:
	LevelGrid* _parentGrid = nullptr;
	vector<LevelGrid*> _childGrids;
	vector<Room*> _rooms;
};
