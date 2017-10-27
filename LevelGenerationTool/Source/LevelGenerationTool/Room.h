#pragma once

#include "CoreMinimal.h"
#include "BaseGrid.h"
#include "Tile.h"
#include <vector>
#include "Runtime/Core//Public/Math/Vector2D.h"
#include "Entity.h"

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
	vector<Tile*> GetEdges();

	int GetLeft() { return _tiles[0][0]->_x; }
	int GetBottom() { return _tiles[0][0]->_y; }
	int GetRight() { return _tiles[_width - 1][0]->_x; }
	int GetTop() { return _tiles[0][_height - 1]->_y; }
	Tile* GetCenterTile();
	FVector2D GetCenterPos();

	int GetRoomSize() { return _width * _height; }
	bool IsCorner(const int x, const int y);

	// Connect
	void AddConnection(Room* room) { _connectedRooms.push_back(room); }
	vector<Room*> GetConnectedRooms() { return _connectedRooms; }

	// Inter room functions
	int GetShortestDistance(Room* other, int& distance);

	// Fill
	void AddLevelStart();
	void AddLevelEnd();
	void PlaceEntitiesOnEdges(vector<Entity*> entities);
	void AddAlcove(Entity* entity);

private:
	vector<Room*> _connectedRooms;
};