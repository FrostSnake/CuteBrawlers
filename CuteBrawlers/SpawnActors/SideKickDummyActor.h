// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnAbilityActor.h"
#include "Components/SphereComponent.h"
#include "SideKickDummyActor.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class CUTEBRAWLERS_API ASideKickDummyActor : public ASpawnAbilityActor
{
	GENERATED_BODY()
	
private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void OnInit_Implementation() override;


public:
	// Sets default values for this actor's properties
	ASideKickDummyActor();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SideKick)
		float Lifetime = 0.75f;
	UPROPERTY(BlueprintReadOnly, Category = SideKick)
		float KickingPower = 200;


	UFUNCTION(BlueprintCallable, Category = SideKick)
		void SetPower(float power) { KickingPower = power; }
	



	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		USphereComponent* Collider;
};
