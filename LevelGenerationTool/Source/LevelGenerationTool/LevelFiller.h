#pragma once

#include "CoreMinimal.h"
#include "LevelGrid.h"

class LEVELGENERATIONTOOL_API LevelFiller
{
public:
	LevelFiller(LevelGrid* pGrid) : _pGrid(pGrid) { _rooms = _pGrid->GetChildRoomsDeep(); }
	~LevelFiller();

	void FillRooms();

private:
	LevelGrid* _pGrid;
	vector<Room*> _rooms;

	/* ----------------------- */
	/* --- fill parameters --- */
	/* ----------------------- */

	float _pickupDensity = 0;					// Actual spawns / maximum spawns
	float _pickupPathSpawnRate = 0;				// Chance to spawn on path rooms vs off path rooms
	float _pickupCenterSpawnRate = 0;			// Chance to spawn in the center of rooms vs at the edges
	float _pickupAlcoveRate = 0;				// Chance of edge spawns to generate an alcove
	//float _pickupCorridorAlcoveRate = 0;		// Chance to create alcoves in corridors with a spawn

	float _enemyDensity = 0;					// Actual spawns / maximum spawns
	float _enemyPathSpawnRate = 0;				// Chance to spawn on path rooms vs off path rooms
	float _enemyCenterSpawnRate = 0;			// Chance to spawn in the center of rooms vs at the edges
	float _enemyAlcoveRate = 0;					// Chance of edge spawns to generate an alcove
	//float _enemyCorridorAlcoveRate = 0;		// Chance to create alcoves in corridors with a spawn

	int _maxLockedDoors = 0;
	float _lockedDoorDensity = 0;				// Actual spawns / maximum spawns
	//float _secretRoomDensity = 0;				// Secret rooms / off path rooms
};
