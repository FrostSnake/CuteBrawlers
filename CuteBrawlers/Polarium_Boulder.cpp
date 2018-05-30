// Fill out your copyright notice in the Description page of Project Settings.

#include "Polarium_Boulder.h"


// Sets default values
APolarium_Boulder::APolarium_Boulder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Boulder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Boulder"));
	SetRootComponent(Boulder);
	Boulder->SetSimulatePhysics(true);
	Boulder->SetMassOverrideInKg(NAME_None, 1500, true);

}

// Called when the game starts or when spawned
void APolarium_Boulder::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APolarium_Boulder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APolarium_Boulder::Launch(float speed)
{
	Boulder->SetSimulatePhysics(true);
	Boulder->SetAllPhysicsLinearVelocity(GetActorForwardVector() * speed);

}

