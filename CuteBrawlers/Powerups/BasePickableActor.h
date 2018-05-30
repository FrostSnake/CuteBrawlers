// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BasePickableActor.generated.h"

class ACuteBrawlersCharacter;
enum class EAttachmentPoint : uint8;
UCLASS(ABSTRACT, Blueprintable)
class CUTEBRAWLERS_API ABasePickableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = PickableActor)
		//Sets bPickedup to true
		void AttachToBrawler(ACuteBrawlersCharacter* brawler);

	UFUNCTION(BlueprintNativeEvent, Category = PickableActor)
		bool CanPickup(ACuteBrawlersCharacter* brawler);
	virtual bool CanPickup_Implementation(ACuteBrawlersCharacter* brawler);

	UFUNCTION(BlueprintNativeEvent, Category = PickableActor)
		void OnPickup(ACuteBrawlersCharacter* brawler);
	virtual void OnPickup_Implementation(ACuteBrawlersCharacter* brawler);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PickableActor)
		bool bDestroyOnPickup = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PickableActor, Meta = (EditCondition = "!bDestroyOnPickup"))
		bool bAttachToBrawlerOnPickup = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = PickableActor, Meta = (EditCondition = "bAttachToBrawlerOnPickup"))
		EAttachmentPoint WhereToAttach;
	

	UPROPERTY(BlueprintReadOnly, Category = PickableActor)
		ACuteBrawlersCharacter* ParentBrawler;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		USphereComponent* Collider;
};
