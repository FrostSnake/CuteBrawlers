// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BaseModifier.h"
#include "ModifiersComponent.generated.h"

class ACuteBrawlersCharacter;


UCLASS( ClassGroup=(CuteBrawler), meta=(BlueprintSpawnableComponent) )
class CUTEBRAWLERS_API UModifiersComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UModifiersComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ACuteBrawlersCharacter* Brawler;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void AddModifier(TSubclassOf<ABaseModifier> modifierTemplate);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void RemoveModifier(ABaseModifier* modifier);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void RemoveModifiersOfType(TSubclassOf<ABaseModifier> modifierType);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void RemoveAllModifiers();

	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void AppendModifierEffect(EModifierEffect effect);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void RemoveModifierEffect(EModifierEffect effect);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void RemoveAllModifierEffectsOfType(EModifierEffect effect);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void RemoveAllModifierEffects();

	UFUNCTION(BlueprintCallable, Category = Modifiers)
		bool HasModifierEffect(EModifierEffect effect);

	UFUNCTION(BlueprintCallable, Category = Modifiers)
		//Returns an instance of the supplied modifier type if it could be found in the AttachedModifiers array
		ABaseModifier* FindModifierOfType(TSubclassOf<ABaseModifier> modifierType);


	UFUNCTION(BlueprintCallable, Category = Modifiers)
		ACuteBrawlersCharacter* GetCuteBrawler();
		
	UPROPERTY(BlueprintReadOnly, Category = Modifiers)
		TArray<ABaseModifier*> AttachedModifiers;
	UPROPERTY(BlueprintReadOnly, Category = Modifiers)
		TArray<EModifierEffect> ModifierEffects;
};
