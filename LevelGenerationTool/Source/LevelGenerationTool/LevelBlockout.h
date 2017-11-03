// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include <vector>

#include "Tile.h"
#include "LevelGrid.h"

#include "LevelBlockout.generated.h"

using namespace std;

UCLASS()
class LEVELGENERATIONTOOL_API ALevelBlockout : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelBlockout();

	void SetLayout(vector<vector<Tile*>> tiles, const int width, const int height);
	UFUNCTION(BlueprintCallable, Category = "GridActions")
	void Generate();
	UFUNCTION(BlueprintCallable, Category = "GridSettings")
	void SetBasicBlock(UStaticMesh* mesh) { _pBasicBlock = mesh; }

	void DestroyBlocks();

	FVector GetSpawnLocation() { return _spawnLocation; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnFloor();
	void SpawnBlock(const Tile* tile, const int x, const int y);
	void SpawnDoorTop(const Tile* tile, const int x, const int y);

private:
	UStaticMesh* _pBasicBlock = nullptr;
	vector<vector<Tile*>> _tiles;
	vector<UStaticMeshComponent*> _pMeshes;
	int _width, _height;
	const int BLOCK_SCALE = 2;
	const int BLOCK_SIZE = 100;

	FVector _spawnLocation;

	/* --- COLORS --- */
	FColor _colPathRooms = FColor(235, 235, 235);
	FColor _colOffPathRooms = FColor(175, 175, 175);
};
