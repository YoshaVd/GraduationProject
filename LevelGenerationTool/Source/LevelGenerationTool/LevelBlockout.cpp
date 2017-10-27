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

void ALevelBlockout::SpawnFloor()
{
	// create mesh component
	UStaticMeshComponent* meshComp = NewObject<UStaticMeshComponent>(this);
	meshComp->SetStaticMesh(_pBasicBlock);

	UMaterialInstanceDynamic* mat = UMaterialInstanceDynamic::Create(_pBasicBlock->GetMaterial(0), this);
	mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::White);
	meshComp->SetMaterial(0, mat);

	// set location depending on array indices
	meshComp->SetWorldScale3D(FVector(_width * BLOCK_SCALE, _height * BLOCK_SCALE, 0));

	// attach/register and add to vector
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	meshComp->AttachToComponent(RootComponent, rules);
	meshComp->RegisterComponentWithWorld(GetWorld());
	_pMeshes.push_back(meshComp);
}

void ALevelBlockout::SpawnBlock(const Tile * tile, const int x, const int y)
{
	// create mesh component
	UStaticMeshComponent* meshComp = NewObject<UStaticMeshComponent>(this);
	meshComp->SetStaticMesh(_pBasicBlock);

	// set color according to tiles
	UMaterialInstanceDynamic* mat = UMaterialInstanceDynamic::Create(_pBasicBlock->GetMaterial(0), this);

	if (tile->_isFilled)
	{
		// set location && scale for walls
		meshComp->SetWorldLocation(FVector(x, y, 0));
		meshComp->SetWorldScale3D(FVector(BLOCK_SCALE, BLOCK_SCALE, 1.5 * BLOCK_SCALE));		
		mat->SetVectorParameterValue(FName(TEXT("Color")), tile->_color);
	}
	else
	{
		// set location && scale for floors
		meshComp->SetWorldLocation(FVector(x, y, -BLOCK_SCALE * BLOCK_SIZE));
		meshComp->SetWorldScale3D(FVector(BLOCK_SCALE, BLOCK_SCALE, BLOCK_SCALE));
		switch (tile->_state)
		{
		case ROOM:
			mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::Silver);
			break;
		case CORRIDOR:
			mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::White);
			break;
		case START_POS:
			_spawnLocation = FVector(x, y, BLOCK_SCALE * BLOCK_SIZE);
			mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::Green);
			break;
		case END_POS:
			mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::Red);
			break;
		case EDGE:
			mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::Yellow);
			break;
		case PICKUP:
			mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::Orange);
			break;
		default:
			break;
		}
	}

	meshComp->SetMaterial(0, mat);

	// attach/register and add to vector
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	meshComp->AttachToComponent(RootComponent, rules);
	meshComp->RegisterComponentWithWorld(GetWorld());
	_pMeshes.push_back(meshComp);
}

void ALevelBlockout::SpawnDoorTop(const Tile * tile, const int x, const int y)
{
	// create mesh component
	UStaticMeshComponent* meshComp = NewObject<UStaticMeshComponent>(this);
	meshComp->SetStaticMesh(_pBasicBlock);

	// set color according to tiles
	UMaterialInstanceDynamic* mat = UMaterialInstanceDynamic::Create(_pBasicBlock->GetMaterial(0), this);
	mat->SetVectorParameterValue(FName(TEXT("Color")), FColor::Cyan);
	meshComp->SetMaterial(0, mat);

	// set location && scale for doortop
	meshComp->SetWorldLocation(FVector(x, y, BLOCK_SCALE * BLOCK_SIZE));
	meshComp->SetWorldScale3D(FVector(BLOCK_SCALE, BLOCK_SCALE, 0.5 * BLOCK_SCALE));

	// attach/register and add to vector
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false);
	meshComp->AttachToComponent(RootComponent, rules);
	meshComp->RegisterComponentWithWorld(GetWorld());
	_pMeshes.push_back(meshComp);
}

void ALevelBlockout::SetLayout(vector<vector<Tile*>> tiles, const int width, const int height)
{
	_tiles = tiles;
	_width = width;
	_height = height;
}

void ALevelBlockout::Generate()
{
	FVector origin(-_width / 2 * BLOCK_SCALE * BLOCK_SIZE, -_height / 2 * BLOCK_SCALE * BLOCK_SIZE, 0);

	// SpawnFloor();

	/* --- SPAWN BLOCKS --- */
	/* -------------------- */
	for (size_t col = 0; col < _tiles.size(); col++)
	{
		for (size_t row = 0; row < _tiles[col].size(); row++)
		{
			SpawnBlock(_tiles[col][row],
				origin.X + col * BLOCK_SCALE * BLOCK_SIZE,
				origin.Y + row * BLOCK_SCALE * BLOCK_SIZE);
			if (_tiles[col][row]->_state == DOOR_NONE)
				SpawnDoorTop(_tiles[col][row], 
					origin.X + col * BLOCK_SCALE * BLOCK_SIZE,
					origin.Y + row * BLOCK_SCALE * BLOCK_SIZE);
		}
	}
}