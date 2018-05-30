// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modifiers/BaseModifier.h"
#include "GhostModifier.generated.h"

/**
 * 
 */
UCLASS(ABSTRACT)
class CUTEBRAWLERS_API AGhostModifier : public ABaseModifier
{
	GENERATED_BODY()
	
	
public:
	// Sets default values for this actor's properties
	AGhostModifier();
	

protected:
	virtual void OnModifierEffectBegan_Implementation() override;
	virtual void OnModifierEffectEnded_Implementation() override;


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Modifiers, Meta = (ClampMin = "0", ClampMax = "1"))
		//[0,1], 1 = opaque
		float GhostTransparency = 0.4f;
};
