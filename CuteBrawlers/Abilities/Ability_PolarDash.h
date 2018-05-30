// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbilityComponent.h"
#include "Ability_PolarDash.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Abilities), meta = (BlueprintSpawnableComponent))
class CUTEBRAWLERS_API UAbility_PolarDash : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UAbility_PolarDash();
	

	virtual void OnCast() override;
	
};
