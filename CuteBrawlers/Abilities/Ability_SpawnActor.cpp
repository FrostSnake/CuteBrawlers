// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_SpawnActor.h"
#include "SpawnAbilityActor.h"
#include "CuteBrawlersCharacter.h"
#include "Engine.h"


UAbility_SpawnActor::UAbility_SpawnActor()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::NO_ABILITY;
	OverridenAbilityType = EAbilityType::NO_ABILITY;
}

EAbilityType UAbility_SpawnActor::GetAbilityType()
{
	return OverridenAbilityType;
}

void UAbility_SpawnActor::PostInitProperties()
{
	Super::PostInitProperties();

	AbilityType = OverridenAbilityType;
}

void UAbility_SpawnActor::BeginPlay()
{
	Super::BeginPlay();

	AbilityType = OverridenAbilityType;
}

void UAbility_SpawnActor::TickAbility(float DeltaTime)
{
	if (SpawningMethod == ESpawnActorType::UntilChannelingEnd)
	{
		ChannelAbilityActor(CurrentChannelingTime / MaxChannelingTime);
	}

	Super::TickAbility(DeltaTime);
}

void UAbility_SpawnActor::SpawnAbilityActor(bool storeReference)
{
	TSubclassOf<ASpawnAbilityActor> spawnTemplate = GetSpawnActorTemplate();
	if (spawnTemplate == NULL)
		return;


	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner()))
	{
		//Spawn actor
		ASpawnAbilityActor* spawned = GetWorld()->SpawnActor<ASpawnAbilityActor>(spawnTemplate, brawler->GetActorLocation(), brawler->Rotator->GetComponentRotation());
		//Initiate it with owning CuteBrawler
		if (spawned)
		{
			spawned->Init(brawler);
		}

		//Store the reference only if we have to
		if (storeReference)
		{
			SpawnedActor = spawned;
		}
	}
}

void UAbility_SpawnActor::ChannelAbilityActor(float currentChannel)
{
	//Call UpdateChannelValue(alpha) method on the spawned actor
	if (SpawnedActor != NULL && !SpawnedActor->IsPendingKill())
	{
		SpawnedActor->UpdateChannelValue(currentChannel);
	}
}
void UAbility_SpawnActor::DestroySpawnedActor()
{
	//Destroy the spawned actor
	if (SpawnedActor != NULL && !SpawnedActor->IsPendingKill())
	{
		SpawnedActor->Destroy();
		SpawnedActor = NULL;
	}
}


void UAbility_SpawnActor::OnCast()
{
	Super::OnCast();

	switch (SpawningMethod)
	{
	case ESpawnActorType::OnCast:
		//Spawn the actor
		SpawnAbilityActor(false);
		break;
	case ESpawnActorType::OnChannelingEnd:
		//Do nothing!
		break;
	case ESpawnActorType::UntilChannelingEnd:
		//Spawn the actor, store a reference of it
		SpawnAbilityActor(true);
		break;
	}
}

void UAbility_SpawnActor::OnChannelEnd()
{
	Super::OnChannelEnd();


	switch (SpawningMethod)
	{
	case ESpawnActorType::OnCast:
		//Do nothing!
		break;
	case ESpawnActorType::OnChannelingEnd:
		//Spawn the actor
		SpawnAbilityActor(true);
		ChannelAbilityActor(CurrentChannelingTime / MaxChannelingTime);
		break;
	case ESpawnActorType::UntilChannelingEnd:
		//Destroy the spawned actor
		DestroySpawnedActor();
		break;
	}
}


TSubclassOf<ASpawnAbilityActor> UAbility_SpawnActor::GetSpawnActorTemplate_Implementation()
{
	return NULL;
}