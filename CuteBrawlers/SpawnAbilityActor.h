// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnAbilityActor.generated.h"


class ACuteBrawlersCharacter;
UCLASS(ABSTRACT)
class CUTEBRAWLERS_API ASpawnAbilityActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnAbilityActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = AbilitySpawnActor)
		//OwningBrawler is initialized at this point.
		void OnInit();
	virtual void OnInit_Implementation() {}
	UFUNCTION(BlueprintNativeEvent, Category = AbilitySpawnActor)
		//Fired each time ChannelValue is updated.
		void OnUpdateChannelValue();
	virtual void OnUpdateChannelValue_Implementation() {}
	UFUNCTION(BlueprintNativeEvent, Category = AbilitySpawnActor)
		//Same as default Tick event, but only ticks when OwningBrawler is properly initialized
		void OnTickInitialized(float DeltaTime);
	virtual void OnTickInitialized_Implementation(float DeltaTime) {}

	UPROPERTY(BlueprintReadOnly, Category = AbilitySpawnActor)
		float ChannelValue = 0;
	UPROPERTY(BlueprintReadOnly, Category = AbilitySpawnActor)
		ACuteBrawlersCharacter* OwningBrawler;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Init(ACuteBrawlersCharacter* brawler);
	void UpdateChannelValue(float alpha);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AbilitySpawnActor)
		bool bAttachToBrawler = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = AbilitySpawnActor)
		bool bKillIfBrawlerDies = false;
	
};
