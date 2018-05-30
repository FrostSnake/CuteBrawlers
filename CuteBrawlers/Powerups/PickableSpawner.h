// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableSpawner.generated.h"




UENUM(BlueprintType)
enum class ESpawningPhases : uint8
{
	//When the spawning system hasn't started yet, or it was suspended.
	STOPPED,
	//Waiting next spawn timer to be done.
	WAITING,
	//Currently spawning pickables
	SPAWNING
};

UENUM(BlueprintType)
enum class ESpawnLocationType : uint8
{
	//Random location in an XYCircle of specific radius
	XYCircle,
	//Random location in an XYRectangle of specific dimensions
	XYRectangle,
	//Uses the overridable method GetCustomSpawnLocation()
	Custom
};

class ABasePickableActor;

USTRUCT(BlueprintType)
struct FSpawnData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PickableSpawner, Meta = (ClampMin = "0"))
		//The probability of spawning this pickable actor
		float Probability;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PickableSpawner)
		//Template class of the desired pickable actor
		TSubclassOf<ABasePickableActor> Template;
	FSpawnData()
	{
		Probability = 1;
		Template = NULL;
	}
};

UCLASS(Blueprintable)
class CUTEBRAWLERS_API APickableSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableSpawner();


private:
	void DoWaitPhase(float DeltaTime);
	void DoSpawningPhase(float DeltaTime);
	FSpawnData & GetNextWeightedSpawnData();
	void FillPickablesToSpawnArray();

	float GetNextWaitTime();
	int32 GetNextSpawnCount();

	ABasePickableActor* SpawnNextPickable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintNativeEvent, Category = PickableSpawner)
		FVector GetCustomSpawnLocation();
	virtual FVector GetCustomSpawnLocation_Implementation() { return GetActorLocation(); }

	UFUNCTION(BlueprintCallable, Category = PickableSpawner)
		FVector GetRandomSpawnLocationInXYCircle();
	UFUNCTION(BlueprintCallable, Category = PickableSpawner)
		FVector GetRandomSpawnLocationInXYRectangle();





	UPROPERTY(BlueprintReadOnly, Category = PickableSpawner)
		ESpawningPhases SpawningPhase = ESpawningPhases::STOPPED;
	UPROPERTY(BlueprintReadOnly, Category = PickableSpawner)
		float TimeToBeginSpawning;


	float TimeToSpawnNextPickable = 0.0f;
	TArray<TSubclassOf<ABasePickableActor>> PickablesToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = PickableSpawner)
		//Starts the spawning system
		void StartSystem(bool resetTimers = true);
	UFUNCTION(BlueprintCallable, Category = PickableSpawner)
		//Stops the spawning system
		void StopSystem();
	UFUNCTION(BlueprintCallable, Category = PickableSpawner)
		//Forces SpawningPhase immediately, optionally reset waiting timer until next spawn
		void ForceSpawn(bool resetTimers);



	UFUNCTION(BlueprintCallable, Category = PickableSpawner)
		bool IsSpawningStarted() { return SpawningPhase != ESpawningPhases::STOPPED; }


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		//if true, debug lines will be drawn in the viewport window.
		bool bDrawDebugLines = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		//if true, the system will automatically start on begin play
		bool bStartSystemOnBeginPlay = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		float SpawnZOffset = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		ESpawnLocationType SpawnLocationType = ESpawnLocationType::XYCircle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		//When SpawnLocationType == XYCircle
		float SpawnLocationCircleRadius = 500;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		//When SpawnLocationType == XYRectangle
		FVector2D SpawnLocationRectangle = FVector2D(250, 250);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner, Meta = (ClampMin = "0"))
		//Minimum wait time until the Spawning phase starts, in seconds.
		float WaitTimeMin = 30;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner, Meta = (ClampMin = "0"))
		//Maximum wait time until the Spawning phase starts, in seconds.
		float WaitTimeMax = 45;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner, Meta = (ClampMin = "0"))
		//Time between spawning each actor during the Spawning phase. Zero means all spawns are created at the same time.
		float SpawningRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner, Meta = (ClampMin = "0"))
		//Minimum number of spawns per Spawning phase.
		int32 SpawnCountMin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner, Meta = (ClampMin = "0"))
		//Maximum number of spawns per Spawning phase.
		int32 SpawnCountMax = 3;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PickableSpawner)
		TArray<FSpawnData> Spawns;
	
};
