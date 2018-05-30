// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Powerups/BasePickableActor.h"
#include "Pickable_Ability.generated.h"


class UBaseAbilityComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class CUTEBRAWLERS_API APickable_Ability : public ABasePickableActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APickable_Ability();
	
protected:
	virtual bool CanPickup_Implementation(ACuteBrawlersCharacter* brawler) override;
	virtual void OnPickup_Implementation(ACuteBrawlersCharacter* brawler) override;


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PickableActor)
		TSubclassOf<UBaseAbilityComponent> AbilityToAdd;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PickableActor, Meta = (ClampMin = "0", ClampMax = "7"))
		int32 AbilitySlotIndex;
	
};
