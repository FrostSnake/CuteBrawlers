// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Polarium_Boulder.generated.h"

UCLASS(ABSTRACT)
class CUTEBRAWLERS_API APolarium_Boulder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APolarium_Boulder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Polarium_Boulder)
		void Launch(float speed);

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		UStaticMeshComponent* Boulder;
};
