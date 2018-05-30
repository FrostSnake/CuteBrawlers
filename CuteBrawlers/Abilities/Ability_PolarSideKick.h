// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Ability_PolarSideKick.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Abilities), meta = (BlueprintSpawnableComponent))
class CUTEBRAWLERS_API UAbility_PolarSideKick : public UBaseAbilityComponent
{
	GENERATED_BODY()
	// Sets default values for this component's properties
	UAbility_PolarSideKick();

	virtual void OnCast() override;
	virtual void OnChannelEnd() override;
	
	
	
};
