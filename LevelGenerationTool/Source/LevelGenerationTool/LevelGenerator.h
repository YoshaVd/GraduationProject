#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGrid.h"
#include "LevelBlockout.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "LevelFiller.h"

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

	/* blockout code */
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void SetBasicBlock(UStaticMesh* mesh) { _pBasicBlock = mesh; }
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void GenerateBlockout();
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		FVector GetSpawnLocation() { return _pLevelBlockout->GetSpawnLocation(); }

	/* test grid functionality*/
	UFUNCTION(BlueprintCallable, Category = "Level Actions")
		void EmptySubGridTest();

	/* set level parameters */
	UFUNCTION(BlueprintCallable, Category = "Level parameters")
		void UpdateLevelContent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALevelBlockout* _pLevelBlockout = nullptr;

	/* ------------------------- */
	/* ----- UI PARAMETERS ----- */
	/* ------------------------- */
	/* --- Layout parameters --- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout parameters")
		int _doubleCorridorPercentage;				// Chance of making a second entrance to the same area
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout parameters")
		int _wideCorridorPercentage;				// Chance of making a corridor twice the width
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout parameters")
		int _granularityDeviation;					// Amount the granularity can randomly deviate upwards
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layout parameters")
		bool _isInsetRandomized;					// Makes inset range between 0 and the specified amount

	/* --- Filler parameters --- */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _pickupDensity = 0.5;					// Actual spawns / maximum spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _pickupPathSpawnRate = 0.5;			// Chance to spawn on path rooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _pickupSideSpawnRate = 0.5;			// Chance to spawn on side rooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _pickupCenterSpawnRate = 0.5;			// Chance to spawn in the center of rooms vs at the edges
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _pickupAlcoveRate = 0.5;				// Chance of edge spawns to generate an alcove

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _enemyDensity = 0.5;					// Actual spawns / maximum spawns
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _enemyPathSpawnRate = 0.5;			// Chance to spawn on path rooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _enemySideSpawnRate = 0.5;			// Chance to spawn on side rooms
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _enemyCenterSpawnRate = 0.5;			// Chance to spawn in the center of rooms vs at the edges
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Filler parameters")
		float _enemyAlcoveRate = 0.5;				// Chance of edge spawns to generate an alcove

private:
	/* --- Functions --- */
	void SetLayoutParamaters(LevelGrid* grid);
	void SetFillerParameters();

	/* --- Members --- */
	LevelGrid* _pGrid = nullptr;
	LevelFiller* _pFiller = nullptr;
	UStaticMesh* _pBasicBlock = nullptr;

	vector<UStaticMeshComponent*> _pMeshes;
};
