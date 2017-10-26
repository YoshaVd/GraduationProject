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
	vector<Tile*> GetEdges();
	void PlaceOnEdges(vector<Entity*> entities);

	int GetLeft() { return _tiles[0][0]->_x; }
	int GetBottom() { return _tiles[0][0]->_y; }
	int GetRight() { return _tiles[_width - 1][0]->_x; }
	int GetTop() { return _tiles[0][_height - 1]->_y; }
	Tile* GetCenterTile();

	bool IsConnectedTo(const FVector2D pos);
	bool IsConnectedTo(const Room& room);
	bool IsCorner(const int x, const int y);

	// Connect
	void ConnectToRoom(Room* room) { _connectedRooms.push_back(room); }

	// Fill
	void AddLevelStart();
	void AddLevelEnd();

private:
	vector<Room*> _connectedRooms;
};