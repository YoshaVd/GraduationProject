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

	void SetLayout(vector<vector<Tile>> tiles) { _tilesArr = tiles; }
	UFUNCTION(BlueprintCallable, Category = "GridActions")
	void GenerateBlockout();
	UFUNCTION(BlueprintCallable, Category = "GridSettings")
	void SetBasicBlock(UStaticMesh* mesh) { _pBasicBlock = mesh; }

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UStaticMesh* _pBasicBlock;
	vector<vector<Tile>> _tilesArr;
};
