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

	while (!visited.empty())
	{
		vector<FVector2D> adjacentTiles = _pGrid->GetAdjacentPositions(current);
		vector<FVector2D> isolatedAdjTiles = _pGrid->GetIsolatedPositionsException(adjacentTiles, current);
		while (isolatedAdjTiles.size() == 0 && !visited.empty())
		{
			visited.pop();
			if (visited.empty())
				break;

			current = visited.top();
			adjacentTiles = _pGrid->GetAdjacentPositions(current);
			isolatedAdjTiles = _pGrid->GetIsolatedPositionsException(adjacentTiles, current);
		}

		if (visited.empty())
			break;

		current = isolatedAdjTiles[rand() % isolatedAdjTiles.size()];
		visited.push(current);
		_pGrid->GetTileLayout()[current.X][current.Y]._isFilled = false;
	}
}

void ALevelGenerator::GenerateBlockout()
{
	if (!_pGrid)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid grid object."));
		return;
	}
	if (!_pBasicBlock)
	{
		UE_LOG(LogTemp, Warning, TEXT("No valid block object."));
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
