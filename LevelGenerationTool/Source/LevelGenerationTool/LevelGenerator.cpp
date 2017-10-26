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
	LevelGrid * grid = _pGrid;
	grid->SplitDeep(granularity);
	grid->AddRoomToChildrenDeep(roomInset);
	grid->ConnectRoomsDeep();
}

void ALevelGenerator::DelaunayTriangulation()
{
	LevelGrid * grid = _pGrid;
	grid->SplitDeep(6);
	grid->AddRoomToChildrenDeep(2);
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
	_pLevelBlockout->Generate();
}

void ALevelGenerator::EmptyAdjacent(int x, int y)
{
	auto adj = _pGrid->GetAdjacentPositions(x, y);
	for (auto a : adj)
	{
		_pGrid->SetFilled(a);
	}
}

void ALevelGenerator::EmptySurround(int x, int y)
{
	auto sur = _pGrid->GetSurroundingPositions(x, y);
	for (auto s : sur)
	{
		_pGrid->SetFilled(s);
	}
}

void ALevelGenerator::EmptySubGridTest()
{
	//LevelGrid* grid = _pGrid->CreateSubGrid(1, 1, _pGrid->GetHeight() - 2, _pGrid->GetWidth() - 2);
	//grid->SetColorAll(FColor::Blue);
	//grid->LogTiles();
	//grid = grid->CreateSubGrid(1, 1, grid->GetHeight() - 2, grid->GetWidth() - 2);
	//grid->SetColorAll(FColor::Red);
	//grid->LogTiles();

	//grid->SetFilledSet(grid->GetTiles(), false);
	//UE_LOG(LogTemp, Warning, TEXT("new grid:"));
	//grid->LogTiles();
	//UE_LOG(LogTemp, Warning, TEXT("original grid:"));
	//_pGrid->LogTiles();

	auto path = _pGrid->FindPath(FVector2D(0, 0), FVector2D(2, 5));
	for (auto p : path)
	{
		_pGrid->SetColor(p, FColor::Yellow);
	}
	_pGrid->SetColor(FVector2D(2, 5), FColor::Red);
}