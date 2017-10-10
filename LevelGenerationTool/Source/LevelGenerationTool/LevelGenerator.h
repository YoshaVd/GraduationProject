#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGrid.h"
#include "LevelBlockout.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

#include "LevelGenerator.generated.h"

UCLASS()
class LEVELGENERATIONTOOL_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelGenerator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void ResetLevel();
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void PerfectMaze();
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void GenerateBlockout();
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void NewGrid(const int width, const int height) { _pGrid = new LevelGrid(width, height); }

	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void SetBasicBlock(UStaticMesh* mesh) { _pBasicBlock = mesh; }

private:
	LevelGrid* _pGrid = nullptr;
	ALevelBlockout* _pLevelBlockout = nullptr;
	UStaticMesh* _pBasicBlock = nullptr;
};
