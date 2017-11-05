#include "LevelGenerator.h"
#include <stack>
#include "Runtime/Core//Public/Math/Vector2D.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

ALevelGenerator::ALevelGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelGenerator::ResetLevel()
{
	int width = _pGrid->GetWidth();
	int height = _pGrid->GetHeight();

	for (auto mesh : _pMeshes)
	{
		if(mesh->IsValidLowLevel())
			mesh->DestroyComponent();
	}
	_pMeshes.clear();
	delete _pGrid;

	_pGrid = new LevelGrid(width, height);
}

void ALevelGenerator::PerfectMaze()
{
	/*	generates a perfect maze: 2 positions will always have exactly one connection	*/
	// start stack with random filled tile and empty it
	LevelGrid* grid = _pGrid->CreateSubGrid(1, 1, _pGrid->GetHeight() - 2, _pGrid->GetWidth() - 2);
	stack<FVector2D> visited;
	FVector2D current = grid->GetRandomPos(true);
	if (!grid->IsWithinBounds(current, "ALevelGenerator::PerfectMaze"))
	{
		UE_LOG(LogTemp, Error, TEXT("PerfectMaze:: current position is out of bounds, terminate function"));
		return;
	}
	visited.push(current);
	grid->SetFilled(current, false);

	// continue looking for options as long as the stack is not empty
	while (!visited.empty())
	{
		// check for isolated adjacent tiles
		vector<FVector2D> adjacentTiles = grid->GetEmptyAdjacentPositions(current);
		vector<FVector2D> isolatedAdjTiles = grid->GetIsolatedPositionsExclusion(adjacentTiles, current);
		// if there are none, pop the stack and try the next one
		while (isolatedAdjTiles.size() == 0 && !visited.empty())
		{
			visited.pop();
			if (visited.empty())
				break;

			current = visited.top();
			adjacentTiles = grid->GetEmptyAdjacentPositions(current);
			isolatedAdjTiles = grid->GetIsolatedPositionsExclusion(adjacentTiles, current);
		}
		if (visited.empty())
			break;

		// choose a random tile from the adjacent isolated tiles and continue from there
		current = isolatedAdjTiles[rand() % isolatedAdjTiles.size()];
		visited.push(current);
		grid->SetFilled(current, false);
	}
}

void ALevelGenerator::RandomWalk(const int steps, const FVector2D start)
{
	/*	generates a random walk area: [steps] amount of adjacent tiles will be emptied	*/
	// set the correct starting values and empty the first tile
	FVector2D current;
	if (start != FVector2D(-1, -1) && _pGrid->IsWithinBounds(start, "ALevelGenerator::RandomWalk"))
		current = start;
	else
		current = _pGrid->GetRandomPos(true);
	_pGrid->SetFilled(current, false);

	stack<FVector2D> visited;
	visited.push(start);

	// loop over the amount of steps
	vector<FVector2D> adjacentEmpties;
	for (size_t i = 1; i < steps; i++)
	{
		// get the adjacent empty tiles, if there are none pop the stack and try again
		adjacentEmpties = _pGrid->GetEmptyAdjacentPositions(current);
		while (adjacentEmpties.size() == 0 && !visited.empty())
		{
			visited.pop();
			if (visited.empty())
				break;

			current = visited.top();
			adjacentEmpties = _pGrid->GetEmptyAdjacentPositions(current);
		}
		if (visited.empty())
			break;

		// get a random position from the adjacent empties, push it on the stack and empty it
		current = _pGrid->GetRandomPosFromSet(adjacentEmpties);
		visited.push(current);
		_pGrid->SetFilled(current, false);
	}
}

void ALevelGenerator::RandomWalkBiased(const int steps, const FVector2D start, const FVector2D target)
{
	/*	generates a random walk area with a bias: [steps] amount of adjacent tiles will be emptied 
		with a bias towards the position [target]	*/
	// set the correct starting values and empty the first tile
	FVector2D current;
	if (_pGrid->IsWithinBounds(start, "ALevelGenerator::RandomWalkBiased"))
		current = start;
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Start for biased random walk is out of bounds"));
		return;
	}
	if (!_pGrid->IsWithinBounds(target, "ALevelGenerator::RandomWalkBiased"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target for biased random walk is out of bounds"));
		return;
	}
	_pGrid->SetFilled(current, false);

	stack<FVector2D> visited;
	visited.push(start);

	vector<FVector2D> adjacentEmpties;
	for (size_t i = 1; i < steps; i++)
	{
		// get the adjacent empty tiles, if there are none pop the stack and try again
		adjacentEmpties = _pGrid->GetEmptyAdjacentPositions(current);
		while (adjacentEmpties.size() == 0 && !visited.empty())
		{
			visited.pop();
			if (visited.empty())
				break;

			current = visited.top();
			adjacentEmpties = _pGrid->GetEmptyAdjacentPositions(current);
		}
		if (visited.empty())
			break;

		// get a random position from the adjacent empties, push it on the stack and empty it
		current = _pGrid->GetRandomPosFromSetBiased(adjacentEmpties, target);
		visited.push(current);
		_pGrid->SetFilled(current, false);
	}

}

void ALevelGenerator::PartitionSpace(const int granularity, const int roomInset)
{
	if (granularity < 1 + roomInset * 2) {
		UE_LOG(LogTemp, Error, TEXT("ALevelGenerator::PartitionSpace || Granularity/inset ratio too low."));
		return;
	}
	LevelGrid* pGrid = new LevelGrid(*_pGrid);
	pGrid =	_pGrid->CreateSubGrid(1, 1, _pGrid->GetHeight() - 2, _pGrid->GetWidth() - 2);
	_pGrid->AddChild(pGrid);

	SetLayoutParamaters(_pGrid);
	pGrid->SplitDeep(granularity);
	_pGrid->AddRoomToChildrenDeep(roomInset);
	_pGrid->ConnectRoomsDeep();

	/* ------------------- */
	/* --- Start & End --- */
	vector<Room*> rooms = _pGrid->GetChildRoomsDeep();
	if (rooms.size() < 2)
		return;

	// place start and end
	rooms.back()->AddLevelEnd();
	Room* startRoom = _pGrid->GetFurthestRoom(rooms, rooms.back());
	startRoom->AddLevelStart();

	// flag rooms and set depths
	auto path = _pGrid->FindShortestPathBFS(startRoom->GetCenterPos(), rooms.back()->GetCenterPos(), false);
	_pGrid->FlagRoomsOnPath(path, ON_PATH);
	_pGrid->SetRoomDepths();
	
	/* --- door & key test ---*/
	_pGrid->GetTopTile(startRoom->GetCenterTile())->_state = KEY;
	vector<Tile*> tiles;
	for (auto col : rooms.back()->GetTiles())
	{
		for (auto tile : col)
		{
			tiles.push_back(tile);
		}
	}
	tiles = _pGrid->GetTilesWithState(tiles, DOOR_NONE);
	for (auto t : tiles)
	{
		t->_state = DOOR_LOCKED;
	}
	/* ---------------------- */

	/* ------------------ */
	/* --- Fill level --- */
	_pFiller = new LevelFiller(_pGrid);
	SetFillerParameters();
	_pFiller->FillRoomsWithLoot();
	_pFiller->FillRoomsWithEnemies();

	/* -------------------- */
	/* --- Display Path --- */
	for (auto t : path)
	{
		_pGrid->SetColor(t, FColor::Yellow);
		if(t->_state == ROOM)
			_pGrid->SetTileState(t, PATH);
	}


}

void ALevelGenerator::GenerateBlockout()
{
	if (!_pGrid) {
		UE_LOG(LogTemp, Error, TEXT("No valid grid object."));
		return;
	}
	if (!_pBasicBlock) {
		UE_LOG(LogTemp, Error, TEXT("No valid block object."));
		return;
	}

	if (_pLevelBlockout) {
		_pLevelBlockout->DestroyBlocks();
		_pLevelBlockout->Destroy();
	}
	_pLevelBlockout = GetWorld()->SpawnActor<ALevelBlockout>();
	_pLevelBlockout->SetLayout(_pGrid->GetTiles(), _pGrid->GetWidth(), _pGrid->GetHeight());
	_pLevelBlockout->SetBasicBlock(_pBasicBlock);
	_pLevelBlockout->GenerateSpawnData();
	_pLevelBlockout->Generate();
}

void ALevelGenerator::EmptySubGridTest()
{
	_pGrid->SplitDeep(7);
	_pGrid->AddRoomToChildrenDeep(2);

	FVector2D start(1, 1);
	FVector2D end(rand() % 30, rand() % 30);

	auto path = _pGrid->FindShortestPathBFS(start, end, true);
	for (auto p : path)
	{
		_pGrid->SetColor(p, FColor::Yellow);
	}
	_pGrid->SetColor(start, FColor::Green);
	_pGrid->SetColor(end, FColor::Red);
}

void ALevelGenerator::UpdateLevelContent()
{
	_pFiller->EmptyRooms();
	SetFillerParameters();
	_pFiller->FillRoomsWithLoot();
	_pFiller->FillRoomsWithEnemies();
	GenerateBlockout();
}

void ALevelGenerator::SetLayoutParamaters(LevelGrid* grid)
{
	if (!grid) return;

	grid->SetOddsWideCorridor(_wideCorridorPercentage);
	grid->SetOddsDoubleCorridor(_doubleCorridorPercentage);
	grid->SetGranularityDeviation(_granularityDeviation);
	grid->SetInsetRandomized(_isInsetRandomized);
}

void ALevelGenerator::SetFillerParameters()
{
	if (!_pFiller) return;

	_pFiller->SetPickupDensity(_pickupDensity);
	_pFiller->SetPickupPathSpawnrate(_pickupPathSpawnRate);
	_pFiller->SetPickupCenterSpawnrate(_pickupCenterSpawnRate);
	_pFiller->SetPickupAlcoveSpawnrate(_pickupAlcoveRate);

	_pFiller->SetEnemyDensity(_enemyDensity);
	_pFiller->SetEnemyPathSpawnrate(_enemyPathSpawnRate);
	_pFiller->SetEnemyCenterSpawnrate(_enemyCenterSpawnRate);
	_pFiller->SetEnemyAlcoveSpawnrate(_enemyAlcoveRate);
}
