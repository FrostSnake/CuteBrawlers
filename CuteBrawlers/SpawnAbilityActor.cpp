// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnAbilityActor.h"
#include "CuteBrawlersCharacter.h"
#include "StatsComponent.h"


// Sets default values
ASpawnAbilityActor::ASpawnAbilityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnAbilityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (OwningBrawler)
	{
		if (bKillIfBrawlerDies && !OwningBrawler->Stats->IsAlive())
		{
			Destroy();
			return;
		}
		OnTickInitialized(DeltaTime);
	}
}

void ASpawnAbilityActor::Init(ACuteBrawlersCharacter * brawler)
{
	if (OwningBrawler == NULL && brawler)
	{
		OwningBrawler = brawler;
		if (bAttachToBrawler)
			AttachToComponent(OwningBrawler->GetRootComponent(),FAttachmentTransformRules::KeepWorldTransform);
		OnInit();
	}
}

void ASpawnAbilityActor::UpdateChannelValue(float alpha)
{
	if (OwningBrawler)
	{
		ChannelValue = alpha;
		OnUpdateChannelValue();
	}
}

