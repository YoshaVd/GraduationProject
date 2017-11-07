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

	delete _pGrid;
	_pGrid = new LevelGrid(width, height);
	SetLayoutParamaters(_pGrid);
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
	/* --- Set up subgrid --- */
	LevelGrid* pGrid = new LevelGrid(*_pGrid);
	pGrid =	_pGrid->CreateSubGrid(1, 1, _pGrid->GetHeight() - 2, _pGrid->GetWidth() - 2);
	_pGrid->AddChild(pGrid);

	/* --- Generate SEED --- */
	ResetRandomOffsets();
	if(_generateNewSeed && _useSeeding)
		_randomSeed = rand();
	_pGrid->SetRandomSeed(_randomSeed);
	pGrid->SetRandomSeed(_randomSeed);

	/* --- Generate layout --- */
	SetLayoutParamaters(pGrid);
	pGrid->SplitDeep(granularity);
	_pGrid->AddRoomToChildrenDeep(roomInset);
	_pGrid->ConnectRoomsDeep();

	/* --- Fill level --- */
	_pFiller = new LevelFiller(_pGrid);
	_pFiller->SetStartAndEnd();
	SetFillerParameters();
	_pFiller->FillRoomsWithLoot();
	_pFiller->FillRoomsWithEnemies();
	_pFiller->AddLockedDoorAndKey();
	_pFiller->AddHiddenRoom();
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
	_pGrid->SetRandomSeed(2534);
	SetLayoutParamaters(_pGrid);
	_pGrid->SplitDeep(7);
	_pGrid->AddRoomToChildrenDeep(0);

}

void ALevelGenerator::UpdateLevelContent()
{
	ResetRandomOffsets();

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
	grid->SetSeedingEnabled(_useSeeding);
}

void ALevelGenerator::SetFillerParameters()
{
	if (!_pFiller) return;

	_pFiller->SetPickupDensity(_pickupDensity);
	_pFiller->SetPickupPathSpawnrate(_pickupPathSpawnRate);
	_pFiller->SetPickupSideSpawnrate(_pickupSideSpawnRate);
	_pFiller->SetPickupCenterSpawnrate(_pickupCenterSpawnRate);
	_pFiller->SetPickupAlcoveSpawnrate(_pickupAlcoveRate);

	_pFiller->SetEnemyDensity(_enemyDensity);
	_pFiller->SetEnemyPathSpawnrate(_enemyPathSpawnRate);
	_pFiller->SetEnemySideSpawnrate(_enemySideSpawnRate);
	_pFiller->SetEnemyCenterSpawnrate(_enemyCenterSpawnRate);
	_pFiller->SetEnemyAlcoveSpawnrate(_enemyAlcoveRate);
}

void ALevelGenerator::ResetRandomOffsets()
{
	auto grids = _pGrid->GetChildrenDeep();
	for (auto g : grids) g->SetSeedOffset(0);
	auto rooms = _pGrid->GetChildRoomsDeep();
	for (auto r : rooms) r->SetSeedOffset(0);
}
