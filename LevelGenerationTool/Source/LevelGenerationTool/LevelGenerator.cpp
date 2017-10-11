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

void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelGenerator::ResetLevel()
{
}

void ALevelGenerator::PerfectMaze()
{
	// start stack with random set of tile coordinates
	stack<FVector2D> visited;
	FVector2D current = _pGrid->GetRandomPos();
	visited.push(current);

	_pGrid->GetTileLayout()[current.X][current.Y]._isFilled = false;
	//int loopCount = 0;
	while (!visited.empty())
	{
		//loopCount++;
		//if (loopCount > 10)
		//	break;

		vector<FVector2D> adjacentTiles = _pGrid->GetEmptyAdjacentPositions(current);
		vector<FVector2D> isolatedAdjTiles = _pGrid->GetIsolatedPositionsExclusion(adjacentTiles, current);
		while (isolatedAdjTiles.size() == 0 && !visited.empty())
		{
			//UE_LOG(LogTemp, Warning, TEXT("-----[[POP]]-----"));

			visited.pop();
			if (visited.empty())
				break;

			current = visited.top();
			adjacentTiles = _pGrid->GetEmptyAdjacentPositions(current);
			isolatedAdjTiles = _pGrid->GetIsolatedPositionsExclusion(adjacentTiles, current);
		}

		if (visited.empty())
			break;

		current = isolatedAdjTiles[rand() % isolatedAdjTiles.size()];
		//UE_LOG(LogTemp, Warning, TEXT("-----[[PUSH]]-----"));
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
	auto tiles = _pGrid->GetTileLayout();
	for (size_t c = 0; c < tiles.size(); c++)
	{
		for (size_t r = 0; r < tiles[c].size(); r++)
		{
			if (tiles[c][r]._isFilled)
			{
				UStaticMeshComponent* Test = NewObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass());
				Test->SetStaticMesh(_pBasicBlock);
				Test->SetWorldLocation(FVector(c * 100, r * 100, 0));
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
