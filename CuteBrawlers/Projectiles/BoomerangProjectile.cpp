// Fill out your copyright notice in the Description page of Project Settings.

#include "BoomerangProjectile.h"


ABoomerangProjectile::ABoomerangProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	Collider->bGenerateOverlapEvents = true;

	bMaintainGroundZ = true;
}

void ABoomerangProjectile::OnProjectileLaunched_Implementation()
{
	Super::OnProjectileLaunched_Implementation();
	AddActorLocalRotation(FRotator(0,InitialYawOffset,0));
}

void ABoomerangProjectile::OnProjectileMove_Implementation(float DeltaTime)
{
	FVector offset = FVector::ForwardVector * Speed * DeltaTime;
	float yawOffset = YawChangeSpeed * DeltaTime * angleDirection;
	AddActorLocalOffset(offset);
	AddActorLocalRotation(FRotator(0, yawOffset, 0));

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
			angleDirection *= -1;
			FVector normal = GetActorLocation() - overlappingActors[0]->GetActorLocation();
			normal.Normalize();
			FVector reflection = FMath::GetReflectionVector(GetActorForwardVector(), normal);
			reflection.Z = 0;
			SetActorRotation(reflection.Rotation());
			ImpactIgnoredActors.Empty();
			OnProjectileImpact(overlappingActors[0]);
			if (bKillOnImpact)
			{
				Destroy();
			}
		}
	}
}
