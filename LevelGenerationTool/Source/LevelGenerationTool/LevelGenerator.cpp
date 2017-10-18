#include "LevelGenerator.h"
#include <stack>
#include "Runtime/Core//Public/Math/Vector2D.h"

ALevelGenerator::ALevelGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();
}

//void ALevelGenerator::OnConstruction(const FTransform& transform)
//{
//	if (updateLevel)
//	{
//		PerfectMaze();
//		GenerateBlockout();
//		updateLevel = false;
//	}
//}

void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelGenerator::ResetLevel()
{
}

void ALevelGenerator::PerfectMaze()
{
	LevelGrid* grid = _pGrid->CreateSubGrid(_pGrid->GetHeight() - 1, _pGrid->GetWidth() - 1, 1, 1);
	/* generates a perfect maze: 2 positions will always have exactly one connection */
	// start stack with random filled tile and empty it
	stack<FVector2D> visited;
	FVector2D current = grid->GetRandomPos(true);
	if (!grid->IsWithinBounds(current))
	{
		UE_LOG(LogTemp, Error, TEXT("PerfectMaze:: current position is out of bounds, terminate function"));
		return;
	}
	visited.push(current);
	grid->GetTileLayout()[current.X][current.Y]._isFilled = false;

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
		grid->GetTileLayout()[current.X][current.Y]._isFilled = false;
	}
}

void ALevelGenerator::RandomWalk(const int steps, const FVector2D start)
{
	/* generates a random walk area: [steps] amount of adjacent tiles will be emptied */
	// set the correct starting values and empty the first tile
	FVector2D current;
	if (start != FVector2D(-1, -1) && _pGrid->IsWithinBounds(start))
		current = start;
	else
		current = _pGrid->GetRandomPos(true);
	_pGrid->GetTileLayout()[current.X][current.Y]._isFilled = false;

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
		_pGrid->GetTileLayout()[current.X][current.Y]._isFilled = false;
	}
}

void ALevelGenerator::RandomWalkBiased(const int steps, const FVector2D start, const FVector2D target)
{
	/* generates a random walk area with a bias: [steps] amount of adjacent tiles will be emptied 
	with a bias towards the position [target]*/
	// set the correct starting values and empty the first tile
	FVector2D current;
	if (_pGrid->IsWithinBounds(start))
		current = start;
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Start for biased random walk is out of bounds"));
		return;
	}
	if (!_pGrid->IsWithinBounds(target))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target for biased random walk is out of bounds"));
		return;
	}
	_pGrid->GetTileLayout()[current.X][current.Y]._isFilled = false;

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
		_pGrid->GetTileLayout()[current.X][current.Y]._isFilled = false;
	}

}		

void ALevelGenerator::GenerateBlockout()
{
	if (!_pGrid)
	{
		UE_LOG(LogTemp, Error, TEXT("No valid grid object."));
		return;
	}
	if (!_pBasicBlock)
	{
		UE_LOG(LogTemp, Error, TEXT("No valid block object."));
		return;
	}

	FVector2D origin = FVector2D(-_pGrid->GetWidth()/2 * 100, -_pGrid->GetHeight()/2 * 100);
	auto tiles = _pGrid->GetTileLayout();
	for (size_t c = 0; c < tiles.size(); c++)
	{
		for (size_t r = 0; r < tiles[c].size(); r++)
		{
			if (tiles[c][r]._isFilled)
			{
				UStaticMeshComponent* Test = NewObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass());
				Test->SetStaticMesh(_pBasicBlock);
				Test->SetWorldLocation(FVector(origin.X + c * 100, origin.Y + r * 100, 0));
				Test->RegisterComponentWithWorld(GetWorld());
				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
				Test->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
			}
		}
	}
	//_pLevelBlockout = NewObject<ALevelBlockout>();
	//_pLevelBlockout->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	//_pLevelBlockout->SetLayout(_pGrid->GetTileLayout());
	//_pLevelBlockout->SetBasicBlock(_pBasicBlock);
	//_pLevelBlockout->GenerateBlockout();
}

void ALevelGenerator::EmptyAdjacent(int x, int y)
{
	auto adj = _pGrid->GetAdjacentPositions(x, y);
	for (auto a : adj)
	{
		_pGrid->SetFilled(a.X, a.Y);
	}
}

void ALevelGenerator::EmptySurround(int x, int y)
{
	auto sur = _pGrid->GetSurroundingPositions(x, y);
	for (auto s : sur)
	{
		_pGrid->SetFilled(s.X, s.Y);
	}
}

void ALevelGenerator::EmptySubGridTest()
{
	LevelGrid* grid = _pGrid->CreateSubGrid(_pGrid->GetHeight() - 1, _pGrid->GetWidth() - 1, 1, 1);
	_pGrid->SetFilledSet(grid->GetTileLayout(), true);
}
