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
		void SetPercentage_WideCorridor(const int odds) { _wideCorridorPercentage = odds; }
	UFUNCTION(BlueprintCallable, Category = "Level parameters")
		void SetPercentage_DoubleCorridor(const int odds) { _doubleCorridorPercentage = odds; }
	UFUNCTION(BlueprintCallable, Category = "Level parameters")
		void SetDeviation_Granularity(const int deviation) { _granularityDeviation = deviation; }
	UFUNCTION(BlueprintCallable, Category = "Level parameters")
		void SetRandomized_Inset(const bool enabled) { _isInsetRandomized = enabled; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALevelBlockout* _pLevelBlockout = nullptr;

private:
	LevelGrid* _pGrid = nullptr;
	LevelGrid* _pGridEmptyLayout = nullptr;
	UStaticMesh* _pBasicBlock = nullptr;

	vector<UStaticMeshComponent*> _pMeshes;

	int _doubleCorridorPercentage;
	int _wideCorridorPercentage;
	int _granularityDeviation;
	bool _isInsetRandomized;
};
