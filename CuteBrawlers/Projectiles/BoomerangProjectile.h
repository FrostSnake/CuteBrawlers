// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/BaseProjectile.h"
#include "BoomerangProjectile.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class CUTEBRAWLERS_API ABoomerangProjectile : public ABaseProjectile
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABoomerangProjectile();
	
protected:
	virtual void OnProjectileLaunched_Implementation() override;
	virtual void OnProjectileMove_Implementation(float DeltaTime) override;


public:




	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (ClampMin = "-180", ClampMax = "180"))
		float InitialYawOffset = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (ClampMin = "-180", ClampMax = "180"))
		float YawChangeSpeed = 10.0f;
	
	float angleDirection = 1;
};
