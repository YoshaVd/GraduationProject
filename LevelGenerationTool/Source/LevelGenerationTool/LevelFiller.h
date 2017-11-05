#pragma once

#include "CoreMinimal.h"
#include "LevelGrid.h"

class LEVELGENERATIONTOOL_API LevelFiller
{
public:
	LevelFiller(LevelGrid* pGrid) : _pGrid(pGrid) { _rooms = _pGrid->GetChildRoomsDeep(); }
	~LevelFiller();

	vector<Tile*> GetAlcoveFriendlyTiles(Room* room);
	void FillRoomsWithLoot();
	void FillRoomsWithEnemies();
	void EmptyRooms();

	/* --- SETTERS --- */
	void SetPickupDensity(float density) { _pickupDensity = FMath::Clamp<float>(density, 0, 1); }
	void SetPickupPathSpawnrate(float rate) { _pickupPathSpawnRate = FMath::Clamp<float>(rate, 0, 1); }
	void SetPickupCenterSpawnrate(float rate) { _pickupCenterSpawnRate = FMath::Clamp<float>(rate, 0, 1); }
	void SetPickupAlcoveSpawnrate(float rate) { _pickupAlcoveRate = FMath::Clamp<float>(rate, 0, 1); }

	void SetEnemyDensity(float density) { _enemyDensity = FMath::Clamp<float>(density, 0, 1); }
	void SetEnemyPathSpawnrate(float rate) { _enemyPathSpawnRate = FMath::Clamp<float>(rate, 0, 1); }
	void SetEnemyCenterSpawnrate(float rate) { _enemyCenterSpawnRate = FMath::Clamp<float>(rate, 0, 1); }
	void SetEnemyAlcoveSpawnrate(float rate) { _enemyAlcoveRate = FMath::Clamp<float>(rate, 0, 1); }


private:
	LevelGrid* _pGrid;
	vector<Room*> _rooms;

	/* ----------------------- */
	/* --- fill parameters --- */ 
	/* ----------------------- */

	float _pickupDensity = 0.5;					// Actual spawns / maximum spawns
	float _pickupPathSpawnRate = 0.5;				// Chance to spawn on path rooms vs off path rooms
	float _pickupCenterSpawnRate = 0.5;			// Chance to spawn in the center of rooms vs at the edges
	float _pickupAlcoveRate = 0.5;				// Chance of edge spawns to generate an alcove
	//float _pickupCorridorAlcoveRate = 0;		// Chance to create alcoves in corridors with a spawn

	float _enemyDensity = 0.5;					// Actual spawns / maximum spawns
	float _enemyPathSpawnRate = 0.5;				// Chance to spawn on path rooms vs off path rooms
	float _enemyCenterSpawnRate = 0.5;			// Chance to spawn in the center of rooms vs at the edges
	float _enemyAlcoveRate = 0.5;					// Chance of edge spawns to generate an alcove
	//float _enemyCorridorAlcoveRate = 0;		// Chance to create alcoves in corridors with a spawn

	int _maxLockedDoors = 0.5;
	float _lockedDoorDensity = 0.5;				// Actual spawns / maximum spawns
	//float _secretRoomDensity = 0;				// Secret rooms / off path rooms
};
