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

void ALevelGenerator::PartitionSpace(const int granularity)
{
	LevelGrid * grid = _pGrid;
	grid->SplitDeep(5);
	grid->AddRoomToChildrenDeep();

	/* quick partition test */
	/*if (_pGrid->Split())
	{
		auto children = _pGrid->GetChildren();
		if (children.size() > 0)
		{
			children[0]->SetColorAll(FColor::Red);
			if(children[0]->Split())
			{
				auto childrenRed = children[0]->GetChildren();
				childrenRed[0]->SetColorArea(1, 1, childrenRed[0]->GetHeight() - 2, childrenRed[0]->GetWidth() - 2, FColor(127, 0, 0));
				childrenRed[1]->SetColorArea(1, 1, childrenRed[1]->GetHeight() - 2, childrenRed[1]->GetWidth() - 2, FColor(127, 0, 0));
			}
		}

		if (children.size() > 1)
		{
			children[1]->SetColorAll(FColor::Blue);
			if (children[1]->Split())
			{
				auto childrenBlue = children[1]->GetChildren();
				childrenBlue[0]->SetColorArea(1, 1, childrenBlue[0]->GetHeight() - 2, childrenBlue[0]->GetWidth() - 2, FColor(0, 0, 127));
				childrenBlue[1]->SetColorArea(1, 1, childrenBlue[1]->GetHeight() - 2, childrenBlue[1]->GetWidth() - 2, FColor(0, 0, 127));
			}
		}

	}*/
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
	auto tiles = _pGrid->GetTiles();
	for (size_t c = 0; c < tiles.size(); c++)
	{
		for (size_t r = 0; r < tiles[c].size(); r++)
		{
			if (tiles[c][r]->_isFilled)
			{
				UStaticMeshComponent* test = NewObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass());
				test->SetStaticMesh(_pBasicBlock);
				if (tiles[c][r]->_color != FColor::Black) {
					UMaterialInstanceDynamic* mat = UMaterialInstanceDynamic::Create(_pBasicBlock->GetMaterial(0), this);
					mat->SetVectorParameterValue(FName(TEXT("Color")), tiles[c][r]->_color);
					test->SetMaterial(0, mat);
				}
				_pMeshes.push_back(test);

				test->SetWorldLocation(FVector(origin.X + c * 100, origin.Y + r * 100, 0));
				test->RegisterComponentWithWorld(GetWorld());
				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, false);
				test->AttachToComponent(RootComponent, rules);
			}
		}
	}
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
	LevelGrid* grid = _pGrid->CreateSubGrid(1, 1, _pGrid->GetHeight() - 2, _pGrid->GetWidth() - 2);
	//grid->SetColorAll(FColor::Blue);
	//grid->LogTiles();
	//grid = grid->CreateSubGrid(1, 1, grid->GetHeight() - 2, grid->GetWidth() - 2);
	//grid->SetColorAll(FColor::Red);
	//grid->LogTiles();

	grid->SetFilledSet(grid->GetTiles(), false);
	UE_LOG(LogTemp, Warning, TEXT("new grid:"));
	grid->LogTiles();
	UE_LOG(LogTemp, Warning, TEXT("original grid:"));
	_pGrid->LogTiles();
}