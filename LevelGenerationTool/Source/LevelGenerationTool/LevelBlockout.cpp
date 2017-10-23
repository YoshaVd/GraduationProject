#include "LevelBlockout.h"
#include "LevelGrid.h"
#include "Runtime/Engine/Classes/Engine/World.h"

/* LEVELBLOCKOUT CURRENTLY NOT USED */

ALevelBlockout::ALevelBlockout()
{
	PrimaryActorTick.bCanEverTick = true;
	LevelGrid* pGrid = new LevelGrid(5, 8);
	_tilesArr = pGrid->GetTiles();
}

void ALevelBlockout::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelBlockout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelBlockout::Generate()
{
	for (size_t col = 0; col < _tilesArr.size(); col++)
	{
		for (size_t row = 0; row < _tilesArr[col].size(); row++)
		{
			if (_tilesArr[col][row]->_isFilled)
			{
				FVector location(col * 100, row * 100, 0);
				FRotator rotation(0.0f, 0.0f, 0.0f);
				FActorSpawnParameters SpawnInfo;
				_pMeshes.push_back(GetWorld()->SpawnActor<UStaticMesh>(location, rotation, SpawnInfo));

				//UStaticMeshComponent* Test = NewObject<UStaticMeshComponent>(UStaticMeshComponent::StaticClass());
				//Test->SetStaticMesh(_pBasicBlock);
				//Test->SetWorldLocation(FVector(col * 100, row * 100, 0));
				//Test->RegisterComponentWithWorld(GetWorld());
				//FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
				//Test->AttachToComponent(RootComponent,rules);
			}
		}
	}
}