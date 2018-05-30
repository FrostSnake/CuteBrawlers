// Fill out your copyright notice in the Description page of Project Settings.

#include "PickableSpawner.h"
#include "BasePickableActor.h"
#include "Engine.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

// Sets default values
APickableSpawner::APickableSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(root);
}

void APickableSpawner::DoWaitPhase(float DeltaTime)
{
	TimeToBeginSpawning -= DeltaTime;
	if (TimeToBeginSpawning <= 0)
	{
		TimeToBeginSpawning = GetNextWaitTime();
		SpawningPhase = ESpawningPhases::SPAWNING;
		FillPickablesToSpawnArray();
	}
}

void APickableSpawner::DoSpawningPhase(float DeltaTime)
{
	int32 numOfSpawns = PickablesToSpawn.Num();
	if (numOfSpawns == 0)
	{
		SpawningPhase = ESpawningPhases::WAITING;
		return;
	}

	if (SpawningRate == 0)
	{
		//Spawn all instantly
		for (int i = 0; i < numOfSpawns; i++)
		{
			ABasePickableActor* spawned = SpawnNextPickable();
		}
		//===================
		SpawningPhase = ESpawningPhases::WAITING;
	}
	else
	{
		//Spawn one when convenient
		if (TimeToSpawnNextPickable <= 0)
		{
			ABasePickableActor* spawned = SpawnNextPickable();
			if (PickablesToSpawn.Num() > 0)
			{
				TimeToSpawnNextPickable = SpawningRate;
			}
		}
		else
		{
			TimeToSpawnNextPickable -= DeltaTime;
		}
		//================================
	}
}

FSpawnData & APickableSpawner::GetNextWeightedSpawnData()
{
	// TODO: insert return statement here
	float total = 0;

	for(FSpawnData &elem : Spawns) {
		total += elem.Probability;
	}

	float randomPoint = FMath::FRand() * total;

	int32 num = Spawns.Num();
	for (int i = 0; i < num; i++) {
		if (randomPoint < Spawns[i].Probability) {
			return Spawns[i];
		}
		else {
			randomPoint -= Spawns[i].Probability;
		}
	}
	return Spawns[0];
}

void APickableSpawner::FillPickablesToSpawnArray()
{
	PickablesToSpawn.Empty();

	if (Spawns.Num() == 0)
		return;


	int32 numOfSpawns = GetNextSpawnCount();
	if (numOfSpawns == 0)
		return;

	for (int i = 0; i < numOfSpawns; i++)
	{
		FSpawnData data = GetNextWeightedSpawnData();
		if (data.Template != NULL)
			PickablesToSpawn.Add(data.Template);
	}
}

float APickableSpawner::GetNextWaitTime()
{
	return FMath::FRandRange(WaitTimeMin, WaitTimeMax);
}

int32 APickableSpawner::GetNextSpawnCount()
{
	return FMath::RandRange(SpawnCountMin,SpawnCountMax);
}

ABasePickableActor * APickableSpawner::SpawnNextPickable()
{
	if (PickablesToSpawn.Num() == 0)
		return NULL;

	UClass* templateClass = PickablesToSpawn[0];
	PickablesToSpawn.RemoveAt(0);
	if (templateClass == NULL)
		return NULL;

	FVector spawnLocation;
	switch (SpawnLocationType)
	{
	case ESpawnLocationType::XYCircle:
		spawnLocation = GetRandomSpawnLocationInXYCircle();
		break;
	case ESpawnLocationType::XYRectangle:
		spawnLocation = GetRandomSpawnLocationInXYRectangle();
		break;
	case ESpawnLocationType::Custom:
		spawnLocation = GetCustomSpawnLocation();
		break;
	default:
		spawnLocation = GetActorLocation();
		break;
	}
	FRotator spawnRotation = FRotator(0, FMath::FRandRange(0.0f,360.0f), 0);
	ABasePickableActor* spawned = GetWorld()->SpawnActor<ABasePickableActor>(templateClass,spawnLocation,spawnRotation);
	return spawned;
}

// Called when the game starts or when spawned
void APickableSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (bStartSystemOnBeginPlay)
		StartSystem();
	
}

void APickableSpawner::OnConstruction(const FTransform & Transform)
{
	if (GetWorld()->GetGameState() != NULL)
		return;

	FlushPersistentDebugLines(GetWorld());
	
	if (!bDrawDebugLines)
		return;

	FVector fixedActorLocation = GetActorLocation();
	fixedActorLocation.Z += SpawnZOffset;
	switch (SpawnLocationType)
	{
	case ESpawnLocationType::XYCircle:
		DrawDebugCircle(GetWorld(), fixedActorLocation, SpawnLocationCircleRadius, 32, FColor::Green, true,-1,(uint8)'\000',5,FVector(0,1,0),FVector(1,0,0));
		break;
	case ESpawnLocationType::XYRectangle:
		FVector center = fixedActorLocation;
		FVector p1, p2, p3, p4;
		float halfX = SpawnLocationRectangle.X * 0.5f;
		float halfY = SpawnLocationRectangle.Y * 0.5f;
		p1 = center + FVector(halfX, halfY, 0);
		p2 = center + FVector(-halfX, halfY, 0);
		p3 = center + FVector(-halfX, -halfY, 0);
		p4 = center + FVector(halfX, -halfY, 0);

		DrawDebugLine(GetWorld(), p1, p2, FColor::Green, true, -1, (uint8)'\000', 5);
		DrawDebugLine(GetWorld(), p2, p3, FColor::Green, true, -1, (uint8)'\000', 5);
		DrawDebugLine(GetWorld(), p3, p4, FColor::Green, true, -1, (uint8)'\000', 5);
		DrawDebugLine(GetWorld(), p4, p1, FColor::Green, true, -1, (uint8)'\000', 5);
		break;
	}
}

FVector APickableSpawner::GetRandomSpawnLocationInXYCircle()
{
	float randomRadius = FMath::FRandRange(0, SpawnLocationCircleRadius);
	float randomAngle = FMath::FRandRange(0.0f, 2*PI);
	return GetActorLocation() + FVector(randomRadius * FMath::Cos(randomAngle), randomRadius * FMath::Sin(randomAngle) ,SpawnZOffset);
}

FVector APickableSpawner::GetRandomSpawnLocationInXYRectangle()
{
	float halfX = SpawnLocationRectangle.X * 0.5f;
	float halfY = SpawnLocationRectangle.Y * 0.5f;
	float randomX = FMath::FRandRange(-halfX, halfX);
	float randomY = FMath::FRandRange(-halfY, halfY);
	return GetActorLocation() + FVector( randomX , randomY , SpawnZOffset );
}

// Called every frame
void APickableSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (SpawningPhase)
	{
	case ESpawningPhases::STOPPED:
		break;
	case ESpawningPhases::WAITING:
		DoWaitPhase(DeltaTime);
		break;
	case ESpawningPhases::SPAWNING:
		DoSpawningPhase(DeltaTime);
		break;
	default:
		break;
	}
}

void APickableSpawner::StartSystem(bool resetTimers)
{
	if (!IsSpawningStarted())
	{
		SpawningPhase = ESpawningPhases::WAITING;
	}
	if (resetTimers)
	{
		TimeToBeginSpawning = GetNextWaitTime();
	}
}

void APickableSpawner::StopSystem()
{
	SpawningPhase = ESpawningPhases::STOPPED;
}

void APickableSpawner::ForceSpawn(bool resetTimers)
{
	SpawningPhase = ESpawningPhases::SPAWNING;
	FillPickablesToSpawnArray();

	if (resetTimers)
	{
		TimeToBeginSpawning = GetNextWaitTime();
	}
}

