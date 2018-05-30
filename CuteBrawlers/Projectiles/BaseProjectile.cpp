// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "BaseModifier.h"
#include "CuteBrawlersCharacter.h"
#include "ModifiersComponent.h"
#include "StatsComponent.h"
#include "Engine.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->SetSphereRadius(50);
	Collider->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Collider->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bLaunched && bLaunchOnBeginPlay)
		Launch();
}


void ABaseProjectile::OnProjectileLaunched_Implementation()
{
	if (bMaintainGroundZ && GroundZOffset < 0)
	{
		DetermineGroundZOffset();
	}
}



void ABaseProjectile::OnProjectileMove_Implementation(float DeltaTime)
{
	FVector offset = FVector::ForwardVector * Speed * DeltaTime;
	AddActorLocalOffset(offset);

	DoMaintainZOffset();

	if (bSweepForImpact)
	{
		TArray<AActor*> overlappingActors;
		Collider->GetOverlappingActors(overlappingActors);
		if (bIgnoreSelf)
		{
			overlappingActors.RemoveSingle(GetOwner());
		}
		int num = ImpactIgnoredActors.Num();
		for (int i = 0; i < num; i++)
		{
			overlappingActors.RemoveSingle(ImpactIgnoredActors[i]);
		}
		int numOfOverlaps = overlappingActors.Num();
		if (numOfOverlaps > 0)
		{
			for (int i = 0; i < numOfOverlaps; i++)
			{
				OnProjectileImpact(overlappingActors[i]);
			}
			if (bKillOnImpact)
			{
				Destroy();
			}
		}
	}
}

void ABaseProjectile::OnProjectileImpact_Implementation(AActor* whichActor)
{
	if (whichActor)
	{
		ImpactIgnoredActors.Add(whichActor);
		ApplyImpactDamageToActor(whichActor);
		ApplyImpactModifiersOnActor(whichActor);
	}
}

void ABaseProjectile::OnProjectileEnd_Implementation()
{

}


void ABaseProjectile::ApplyImpactDamageToActor(AActor * whichActor)
{
	if (ImpactDamage > 0 && whichActor)
	{
		if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(whichActor))
		{
			brawler->Stats->ApplyDamageFromLocation(this, ImpactDamage, GetActorLocation());
		}
	}
}

void ABaseProjectile::ApplyImpactModifiersOnActor(AActor * whichActor)
{
	int num = ImpactModifiers.Num();
	if (num > 0 && whichActor)
	{
		if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(whichActor))
		{
			for (int i = 0; i < num; i++)
			{
				brawler->Modifiers->AddModifier(ImpactModifiers[i]);
			}
		}
	}
}

void ABaseProjectile::DetermineGroundZOffset()
{
	FVector traceStart = GetActorLocation();
	FVector traceEnd = traceStart - FVector::UpVector * 500;
	FHitResult hitResult;
	FCollisionObjectQueryParams obParams = FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_GameTraceChannel1));
	
	if (GetWorld()->LineTraceSingleByObjectType(hitResult, traceStart, traceEnd,obParams, FCollisionQueryParams(FName("Ground"), true)))
	{
		GroundZOffset = hitResult.Distance;
	}
	else
	{
		GroundZOffset = 0;
	}
}

void ABaseProjectile::DoMaintainZOffset()
{
	if (bMaintainGroundZ && GroundZOffset > 0)
	{
		FVector traceStart = GetActorLocation();
		FVector traceEnd = traceStart - FVector::UpVector * GroundZOffset;
		FHitResult hitResult;
		FCollisionObjectQueryParams obParams = FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_GameTraceChannel1));

		if (GetWorld()->LineTraceSingleByObjectType(hitResult, traceStart, traceEnd, obParams, FCollisionQueryParams(FName("Ground"), true)))
		{
			SetActorLocation(hitResult.Location + FVector::UpVector * GroundZOffset);
		}
	}
}


// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLaunched)
	{
		OnProjectileMove(DeltaTime);
	}
}

void ABaseProjectile::Destroyed()
{
	Super::Destroyed();

	if (bLaunched)
		OnProjectileEnd();
}

void ABaseProjectile::Launch()
{
	if (!bLaunched)
	{
		bLaunched = true;
		OnProjectileLaunched();
	}
}

