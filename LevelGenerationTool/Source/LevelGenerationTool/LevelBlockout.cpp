#include "LevelBlockout.h"
#include "LevelGrid.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"

ALevelBlockout::ALevelBlockout()
{
	PrimaryActorTick.bCanEverTick = true;
	LevelGrid* pGrid = new LevelGrid(5, 8);
	_tiles = pGrid->GetTiles();
}

void ALevelBlockout::DestroyBlocks()
{
	for (auto m : _pMeshes)
	{
		m->DestroyComponent();
	}
}

void ALevelBlockout::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelBlockout::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelBlockout::SetLayout(vector<vector<Tile*>> tiles, const int width, const int height)
{
	_tiles = tiles;
	_width = width;
	_height = height;
}

void ALevelBlockout::Generate()
{
	FVector2D origin = FVector2D(-_width / 2 * 100, -_height / 2 * 100);
	for (size_t col = 0; col < _tiles.size(); col++)
	{
		for (size_t row = 0; row < _tiles[col].size(); row++)
		{
			if (_tiles[col][row]->_isFilled)
			{
				// create mesh component
				UStaticMeshComponent* meshComp = NewObject<UStaticMeshComponent>(this);
				meshComp->SetStaticMesh(_pBasicBlock);

				// set color according to tiles
				if (_tiles[col][row]->_color != FColor::Black) {
					UMaterialInstanceDynamic* mat = UMaterialInstanceDynamic::Create(_pBasicBlock->GetMaterial(0), this);
					mat->SetVectorParameterValue(FName(TEXT("Color")), _tiles[col][row]->_color);
					meshComp->SetMaterial(0, mat);
				}

				// set location depending on array indices
				meshComp->SetWorldLocation(FVector(origin.X + col * 300, origin.Y + row * 300, 0));
				//meshComp->SetRelativeScale3D(FVector(1.5, 15, 1.5));

				// attach/register and add to vector
				FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
				meshComp->AttachToComponent(RootComponent,rules);
				meshComp->RegisterComponentWithWorld(GetWorld());
				_pMeshes.push_back(meshComp);
			}
		}
	}
}