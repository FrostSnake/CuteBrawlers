// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/BaseAbilityComponent.h"
#include "Ability_SpawnActor.generated.h"


class ASpawnAbilityActor;
UENUM(BlueprintType)
enum class ESpawnActorType : uint8
{
	//Spawns the actor on cast, and leave it spawned
	OnCast,
	//Spawns the actor at the end of the channeling
	OnChannelingEnd,
	//Spawns the actor on cast, and destroys it at the end of the channeling
	UntilChannelingEnd
};
/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = (Abilities), meta = (BlueprintSpawnableComponent))
class CUTEBRAWLERS_API UAbility_SpawnActor : public UBaseAbilityComponent
{
	GENERATED_BODY()
	
	
protected:
	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	virtual void TickAbility(float DeltaTime);

	void SpawnAbilityActor(bool storeReference);
	//currentChannel = [0,1]
	void ChannelAbilityActor(float currentChannel);
	void DestroySpawnedActor();



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		//The unique ability type, to differentiate between all available abilities in the game.
		EAbilityType OverridenAbilityType = EAbilityType::NO_ABILITY;
public:
	// Sets default values for this component's properties
	UAbility_SpawnActor();

	virtual EAbilityType GetAbilityType() override;


	virtual void OnCast() override;
	virtual void OnChannelEnd() override;

	UFUNCTION(BlueprintNativeEvent, Category = Ability)
		TSubclassOf<ASpawnAbilityActor> GetSpawnActorTemplate();
	virtual TSubclassOf<ASpawnAbilityActor> GetSpawnActorTemplate_Implementation();



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
		ESpawnActorType SpawningMethod = ESpawnActorType::OnCast;


	UPROPERTY(BlueprintReadOnly, Category = Ability)
		ASpawnAbilityActor* SpawnedActor;

};
