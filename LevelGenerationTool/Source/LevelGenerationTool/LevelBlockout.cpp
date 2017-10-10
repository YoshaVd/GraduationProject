#include "LevelBlockout.h"
#include "LevelGrid.h"

ALevelBlockout::ALevelBlockout()
	:Super()
{
	PrimaryActorTick.bCanEverTick = true;
	LevelGrid* pGrid = new LevelGrid(5, 8);
	_tilesArr = pGrid->GetTileLayout();
}

void ALevelBlockout::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelBlockout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelBlockout::GenerateBlockout()
{
	for (size_t c = 0; c < _tilesArr.size(); c++)
	{
		for (size_t r = 0; r < _tilesArr[c].size(); r++)
		{
			if (_tilesArr[c][r]._isFilled)
			{
				UStaticMeshComponent* Test = NewObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass());
				Test->SetStaticMesh(_pBasicBlock);
				Test->SetWorldLocation(FVector(c * 100, r * 100, 0));
				Test->RegisterComponentWithWorld(GetWorld());
				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
				Test->AttachToComponent(RootComponent, rules);
			}
		}
	}
}