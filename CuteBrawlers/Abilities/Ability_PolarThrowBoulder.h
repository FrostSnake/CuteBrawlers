// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "Ability_PolarThrowBoulder.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Abilities), meta = (BlueprintSpawnableComponent))
class CUTEBRAWLERS_API UAbility_PolarThrowBoulder : public UBaseAbilityComponent
{
	GENERATED_BODY()
		// Sets default values for this component's properties
		UAbility_PolarThrowBoulder();
	
	virtual void OnCast() override;
	virtual void OnChannelEnd() override;
	
};
