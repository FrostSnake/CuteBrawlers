// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"


UENUM(BlueprintType)
enum class ELifeState : uint8
{
	LS_Alive 	UMETA(DisplayName = "Alive"),
	LS_Dead 	UMETA(DisplayName = "Dead"),
	LS_Paused	UMETA(DisplayName = "Paused")
};

class ACuteBrawlersCharacter;


UCLASS( ClassGroup=(CuteBrawler), meta=(BlueprintSpawnableComponent) )
class CUTEBRAWLERS_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ProcessRegeneration(float DeltaTime);

	ACuteBrawlersCharacter* Brawler;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Stats)
		void ApplyDamage(AActor* source, float damage);
	UFUNCTION(BlueprintCallable, Category = Stats)
		void ApplyDamageFromLocation(AActor* source, float damage, FVector worldLocation);
	UFUNCTION(BlueprintCallable, Category = Stats)
		void Heal(float amount);
	UFUNCTION(BlueprintCallable, Category = Stats)
		void Resurrect();
	UFUNCTION(BlueprintCallable, Category = Stats)
		void ConsumeEnergy(float amount);
	UFUNCTION(BlueprintCallable, Category = Stats)
		void ReplenishEnergy(float amount);
	UFUNCTION(BlueprintCallable, Category = Stats)
		//A Negative value would deduct from the bonuses.
		void AddBonusHPRegen(float amount);
	UFUNCTION(BlueprintCallable, Category = Stats)
		//A Negative value would deduct from the bonuses.
		void AddBonusEnergyRegen(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
		FORCEINLINE bool IsAlive()
		{
			return LifeState != ELifeState::LS_Dead;
		}

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float Hitpoints = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		float MaxHitpoints = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		float HitpointsRegenRate = 0;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float Energy = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		float MaxEnergy = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
		float EnergyRegenRate = 25;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		ELifeState LifeState = ELifeState::LS_Alive;

	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusHPRegen = 0;
	UPROPERTY(BlueprintReadOnly, Category = Stats)
		float BonusEnergyRegen = 0;
};
