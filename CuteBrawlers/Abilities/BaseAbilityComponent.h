// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AbilitiesDataAsset.h"
#include "BaseAbilityComponent.generated.h"


UCLASS( ClassGroup=(Abilities), meta=(BlueprintSpawnableComponent) )
class CUTEBRAWLERS_API UBaseAbilityComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickAbility(float DeltaTime);
	virtual bool Channel(float DeltaTime);
	virtual void InitiateCast();





public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Ability)
	FORCEINLINE bool IsEmptySlot()
	{
		return AbilityType == EAbilityType::NO_ABILITY;
	}

	UFUNCTION(BlueprintCallable, Category = Ability)
	virtual bool CanCast();

	UFUNCTION(BlueprintCallable, Category = Ability)
	FORCEINLINE bool HasRequiredEnergy(float availableEnergy)
	{
		return RequiredEnergy <= availableEnergy;
	}

	UFUNCTION(BlueprintCallable, Category = Ability)
		virtual EAbilityType GetAbilityType();

	UFUNCTION(BlueprintCallable, Category = Ability)
		bool BeginCast(float currentEnergy);
	UFUNCTION(BlueprintCallable, Category = Ability)
		void EndCast();

	virtual void OnCast();
	virtual void OnChannelEnd();

	void RemoveAbilityIfOneShot();

	

	

	

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Ability)
		//The unique ability type, to differentiate between all available abilities in the game.
		EAbilityType AbilityType = EAbilityType::NO_ABILITY;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		//If true, enables using custom parameter instead of the ones found in the AbilitiesDataAsset.
		bool bOverrideDataAsset = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, Meta = (ClampMin = "0", EditCondition = "bOverrideDataAsset"))
		//The amount of energy points needed to cast the ability.
		float RequiredEnergy = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, Meta = (ClampMin = "0", EditCondition = "bOverrideDataAsset"))
		//Time until the ability can be used again after a successful cast.
		float Cooldown = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, Meta = (ClampMin = "0", EditCondition = "bOverrideDataAsset"))
		//The maximum channeling time, if the ability needs it.
		float MaxChannelingTime = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, Meta = (EditCondition = "bOverrideDataAsset"))
		//If false, the brawler will be unable to move while channeling (turning is unaffected though)
		bool bAllowMotionWhileChanneling = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, Meta = (ClampMin = "-1", EditCondition = "bOverrideDataAsset"))
		//Number of charges the ability have. Negative value indicates infinite charges.
		int32 Charges = -1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability, Meta = (EditCondition = "bOverrideDataAsset"))
		//If true, the ability will be removed from the ability slot after a successful cast.
		bool bOneShotAbility = false;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		//Should be set to false when the component is moved outside the Abilities container
		bool bEnabled = true;


	UPROPERTY(BlueprintReadOnly, Category = Ability)
		float CurrentChannelingTime = 0;
	UPROPERTY(BlueprintReadOnly, Category = Ability)
		float CurrentCooldown = 0;
	UPROPERTY(BlueprintReadOnly, Category = Ability)
		bool bAbilityBegunCast = false;
	UPROPERTY(BlueprintReadOnly, Category = Ability)
		bool bAbilityEnded = false;

};
