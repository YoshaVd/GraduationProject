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

	Tile* GetRandomWall();
	vector<Tile*> GetWalls();
	int GetLeft() { return _tiles[0][0]->_x; }
	int GetBottom() { return _tiles[0][0]->_y; }
	int GetRight() { return _tiles[_width - 1][0]->_x; }
	int GetTop() { return _tiles[0][_height - 1]->_y; }
	Tile* GetCenterTile() { return _tiles[_width / 2][_height / 2]; }

	bool IsConnectedTo(const FVector2D pos);
	bool IsConnectedTo(const Room& room);
	bool IsCorner(const int x, const int y);

	void ConnectToRoom(Room* room) { _connectedRooms.push_back(room); }

private:
	vector<Room*> _connectedRooms;
};