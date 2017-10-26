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
		void NewGrid(const int width, const int height) { _pGrid = new LevelGrid(width, height); }

	/* algorithms */
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void PerfectMaze();
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void RandomWalk(const int steps, const FVector2D start = FVector2D(-1,-1));
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void RandomWalkBiased(const int steps, const FVector2D start, const FVector2D target);
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void PartitionSpace(const int granularity = 5, const int roomInset = 0);
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void DelaunayTriangulation();

	/* blockout code */
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void SetBasicBlock(UStaticMesh* mesh) { _pBasicBlock = mesh; }
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void GenerateBlockout();

	/* test grid functionality*/
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void EmptyAdjacent(int x, int y);
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void EmptySurround(int x, int y);
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void EmptySubGridTest();

private:
	LevelGrid* _pGrid = nullptr;
	ALevelBlockout* _pLevelBlockout = nullptr;
	UStaticMesh* _pBasicBlock = nullptr;

	vector<UStaticMeshComponent*> _pMeshes;
};
