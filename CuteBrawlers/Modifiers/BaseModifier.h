// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseModifier.generated.h"


class UModifiersComponent;

UENUM(BlueprintType)
enum class EModifierEffect : uint8
{
	ME_None 	UMETA(DisplayName = "NONE"),
	//Cannot Move, Cannot Turn, Cannot Use Abilities
	ME_Stunned 	UMETA(DisplayName = "Stunned"),			
	//Cannot Be Damaged
	ME_Invulnerable	UMETA(DisplayName = "Invulnerable"),	
	//Cannot Use Abilities
	ME_Silenced	UMETA(DisplayName = "Silenced")					
};


UCLASS(ABSTRACT)
class CUTEBRAWLERS_API ABaseModifier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseModifier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = Modifiers)
		void OnModifierEffectBegan();
	virtual void OnModifierEffectBegan_Implementation();
	UFUNCTION(BlueprintNativeEvent, Category = Modifiers)
		void OnModifierEffectEnded();
	virtual void OnModifierEffectEnded_Implementation();

	void OnModifierTimeEnded();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void InitModifier(UModifiersComponent* container);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		void Remove();
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		//Sets the duration to custom value
		void SetCustomDuration(float newDuration);
	UFUNCTION(BlueprintCallable, Category = Modifiers)
		//Resets the duration to the original value
		void ResetDuration();
	


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Modifiers)
		TArray<EModifierEffect> ModifierEffects;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Modifiers, Meta = (ClampMin = "0"))
		//Zero value indicates infinite duration.
		float Duration = 2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Modifiers)
		//If true, cannot have more than one instance of this modifier per unit. Adding new instance will refresh the duration instead.
		bool bNonStackable = true;
	
	UPROPERTY(BlueprintReadOnly, Category = Modifiers)
		float TimeLeft = 0;
	UPROPERTY(BlueprintReadOnly, Category = Modifiers)
		UModifiersComponent* ModifiersContainer;
};
