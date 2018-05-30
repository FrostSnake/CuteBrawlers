// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Ability_PolarThrowBoomerang.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Abilities), meta = (BlueprintSpawnableComponent))
class CUTEBRAWLERS_API UAbility_PolarThrowBoomerang : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
	// Sets default values for this component's properties
	UAbility_PolarThrowBoomerang();


	virtual void OnCast() override;
	
	
};
