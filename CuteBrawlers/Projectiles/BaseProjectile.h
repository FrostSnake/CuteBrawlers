// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BaseProjectile.generated.h"

class ABaseModifier;

UCLASS(ABSTRACT)
class CUTEBRAWLERS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
		//Fired when the projectile is launched (by calling Launch() method)
		void OnProjectileLaunched();
	virtual void OnProjectileLaunched_Implementation();
	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
		//Fired every tick, overriding this event will override the motion behavior of the projectile
		void OnProjectileMove(float DeltaTime);
	virtual void OnProjectileMove_Implementation(float DeltaTime);
	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
		//Fired when the projectile collides with an actor (if bSweepForImpact is true)
		void OnProjectileImpact(AActor* whichActor);
	virtual void OnProjectileImpact_Implementation(AActor* whichActor);
	UFUNCTION(BlueprintNativeEvent, Category = Projectile)
		//Fired when the projectile is killed.
		void OnProjectileEnd();
	virtual void OnProjectileEnd_Implementation();

	UFUNCTION(BlueprintCallable, Category = Projectile)
		void ApplyImpactDamageToActor(AActor * whichActor);
	UFUNCTION(BlueprintCallable, Category = Projectile)
		void ApplyImpactModifiersOnActor(AActor* whichActor);


	void DetermineGroundZOffset();
	void DoMaintainZOffset();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable, Category = Projectile)
		void Launch();

	UPROPERTY(BlueprintReadOnly, Category = Projectile)
		bool bLaunched = false;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (ClampMin = "0"))
		float Speed = 500.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		bool bLaunchOnBeginPlay = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		//If true, trace for ground and fix Z component to match the original Z offset, preventing the projectile from going through ground in case of ramps.
		bool bMaintainGroundZ = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (EditCondition = "bMaintainGroundZ", ClampMin = "-1"))
		//The minimum Z distance from ground. Negative value allows determining the Z from the projectile's initial location.
		float GroundZOffset = -1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		bool bSweepForImpact = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (EditCondition = "bSweepForImpact"))
		//If true, Owner actor will be ignored from collision
		bool bIgnoreSelf = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (EditCondition = "bSweepForImpact"))
		bool bKillOnImpact = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, Meta = (ClampMin = "0"))
		float ImpactDamage = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile)
		TArray<TSubclassOf<ABaseModifier>> ImpactModifiers;

	UPROPERTY(BlueprintReadOnly, Category = Projectile)
		TArray<AActor*> ImpactIgnoredActors;



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		USphereComponent* Collider;
};
