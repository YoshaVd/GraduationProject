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
	LevelGrid& operator =(const LevelGrid& other);

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
	bool SplitDeep(const int sizeMin = 5, int level = 0);
	bool SplitHorizontal(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight);
	bool SplitVertical(const int sizeMin, LevelGrid& subLeft, LevelGrid& subRight);

	// Room functions
	void AddRoom(int inset = 0);
	void AddRoomToChildrenDeep(const int inset = 0);
	bool ConnectRoomsStraight(Room* roomA, Room* roomB);
	bool ConnectRoomsStraightWide(Room* roomA, Room* roomB);
	bool ConnectRoomsBFS(Room* roomA, Room* roomB);
	void ConnectRoomsDeep();

	vector<Room*> GetChildRoomsDeep();
	Room* GetClosestRoom(vector<Room*> rooms, Room* targetRoom);
	Room* GetFurthestRoom(vector<Room*> rooms, Room* targetRoom);
	TPair<Room*, Room*> GetClosestRoomPair(vector<Room*> roomsA, vector<Room*> roomsB);
	vector<TPair<Tile*, Tile*>> GetClosestStraightPairs(vector<Tile*> setA, vector<Tile*> setB);

	void FlagRoomsOnPath(vector<Tile*> path, RoomType type);
	vector<Room*> GetRoomPathToType(Room* start, RoomType type);
	vector<Room*> GetRoomPath(Room* start, Room* target);
	vector<Room*> GetRoomsBeforeLockedDoor(Room* start);
	void SetRoomDepths();

	// Pathfinding functions
	bool FindStraightPath(Tile* start, Tile* target, vector<Tile*>& path);
	vector<Tile*> FindShortestPathBFS(const FVector2D start, const FVector2D goal, const bool onFilledTiles);

	/* --- UI Parameters --- */
	void SetOddsDoubleCorridor(const int odds) { _oddsDoubleCorridor = odds; }
	void SetOddsWideCorridor(const int odds) { _oddsWideCorridor = odds; }
	void SetGranularityDeviation(const int deviation) { _granularityDeviation = deviation; }
	void SetInsetRandomized(const bool enabled) { _isInsetRandomized = enabled; }

private:
	LevelGrid* _parentGrid = nullptr;
	vector<LevelGrid*> _childGrids;
	vector<Room*> _rooms;

	const int ODDS_BASE = 100;
	int _oddsDoubleCorridor = 20;
	int _oddsWideCorridor = 30;
	int _granularityDeviation = 0;
	bool _isInsetRandomized = false;
};
