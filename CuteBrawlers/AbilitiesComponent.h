// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AbilitiesDataAsset.h"
#include "BaseAbilityComponent.h"
#include "AbilitiesComponent.generated.h"


class ACuteBrawlersCharacter;

UCLASS( ClassGroup=(CuteBrawler), meta=(BlueprintSpawnableComponent) )
class CUTEBRAWLERS_API UAbilitiesComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilitiesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	//virtual void PostInitProperties() override;
	void InitAbilitySlots();

	void ProcessAbilitySlots(float DeltaTime);

	ACuteBrawlersCharacter* Brawler;
	bool bChanneling = false;
	UBaseAbilityComponent* lastAbilityCast;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetIsChanneling(bool isChanneling)
	{
		bChanneling = isChanneling;
	}
	FORCEINLINE void SetLastAbilityCast(UBaseAbilityComponent* ability)
	{
		lastAbilityCast = ability;
	}


	UFUNCTION(BlueprintCallable, Category = Ability)
		void BeginCastAbility(int32 abilitySlotIndex);
	UFUNCTION(BlueprintCallable, Category = Ability)
		void EndCastAbility(int32 abilitySlotIndex);
	UFUNCTION(BlueprintCallable, Category = Ability)
		void EndCastAllAbilities();

	UFUNCTION(BlueprintCallable, Category = Ability)
		void ReplaceAbilityInSlot(int32 whichSlotIndex, TSubclassOf<UBaseAbilityComponent> whichAbilityType, AActor* attachedActor = NULL);

	UFUNCTION(BlueprintCallable, Category = Ability)
		bool IsCastingEnabled();
	UFUNCTION(BlueprintCallable, Category = Ability)
		FORCEINLINE bool IsChanneling() { return bChanneling; }
	UFUNCTION(BlueprintCallable, Category = Ability)
		FORCEINLINE UBaseAbilityComponent* GetLastAbilityCast() { return lastAbilityCast; }

	
	UPROPERTY(BlueprintReadOnly, Category = Ability)
		TArray<UBaseAbilityComponent*> AbilitiesSlots;
	UPROPERTY(BlueprintReadOnly, Category = Ability)
		TArray<AActor*> AttachedPickables;

	UPROPERTY(VisibleDefaultsOnly, Category = Ability, Transient)
		FString Notes = "Ability keys are: \nSpacebar \nQ \nF \nLShift";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		bool bCastingEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		//DataAsset holding all extra necessary data regarding abilities.
		UAbilitiesDataAsset* AbilitiesDataAsset;
};
