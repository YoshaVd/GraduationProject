#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"
#include "Entity.h"

enum RoomType
{
	START,
	NO_TYPE,
	ON_PATH,
	OFF_PATH
};

class LEVELGENERATIONTOOL_API Room : public BaseGrid
{
public:
	Room(vector<vector<Tile*>> tiles);
	Room(const Room& other);
	~Room() {}

	// Space
	Tile* GetRandomWall();
	vector<Tile*> GetWalls();
	vector<FVector2D> GetWallPositions();
	vector<Tile*> GetWallTiles();
	vector<Tile*> GetEdges();
	vector<vector<Tile*>> GetMiddle2D();
	vector<Tile*> GetMiddle();

	int GetLeft() { return _tiles[0][0]->_x; }
	int GetBottom() { return _tiles[0][0]->_y; }
	int GetRight() { return _tiles[_width - 1][0]->_x; }
	int GetTop() { return _tiles[0][_height - 1]->_y; }
	Tile* GetCenterTile();
	FVector2D GetCenterPos();

	int GetRoomSize() { return _width * _height; }
	bool IsCorner(const int x, const int y);

	// Flagging
	bool Contains(TileState state);
	void SetTilesParent();
	void FlagRoom(RoomType type);
	RoomType GetType() { return _type; }
	void SetType(RoomType type) { _type = type; }

	// Connect
	void AddConnection(Room* room, Tile* door);
	vector<TPair<Room*, Tile*>> GetConnections() { return _connections; }
	vector<Room*> GetConnectedRooms();
	vector<Room*> GetConnectedRoomsNotLocked();
	void AddLockedDoorFrom(Room* from);

	int GetDepthLevel() { return _depthLevel; }
	void SetDepthLevel(const int depth) { _depthLevel = depth; }

	// Fill
	void AddLevelStart();
	void AddLevelEnd();
	int GetMaxEdgeEntities();
	int GetMaxCenterEntities();
	void PlaceEntitiesOnEdges(float density, const TileState state, float alcoveDensity = 0, vector<Tile*> alcoveTiles = vector<Tile*>());
	void PlaceEntitiesInCenter(float density, TileState state);
	void AddAlcove(Entity* entity);

private:
	vector<TPair<Room*, Tile*>> _connections; // pointer to connected room + door tile to that room
	RoomType _type = NO_TYPE;
	int _depthLevel = 0;

	const float ENTITY_PER_EDGE = 0.70;
	const float ENTITY_PER_MIDDLE = 1;
};