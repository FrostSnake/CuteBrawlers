// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Ability_ApplyModifier.generated.h"

/**
 * 
 */

class ABaseModifier;


UCLASS(ClassGroup = (Abilities), meta = (BlueprintSpawnableComponent))
class CUTEBRAWLERS_API UAbility_ApplyModifier : public UBaseAbilityComponent
{
	GENERATED_BODY()

protected:
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		//The unique ability type, to differentiate between all available abilities in the game.
		EAbilityType OverridenAbilityType = EAbilityType::NO_ABILITY;
public:
	// Sets default values for this component's properties
	UAbility_ApplyModifier();

	virtual EAbilityType GetAbilityType() override;


	virtual void OnCast() override;
	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		//Array holding type of modifiers to apply upon casting the ability.
		TArray<TSubclassOf<ABaseModifier>> ListOfModifiers;
};
