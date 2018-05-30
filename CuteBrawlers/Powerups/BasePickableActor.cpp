// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickableActor.h"
#include "StatsComponent.h"
#include "CuteBrawlersCharacter.h"


// Sets default values
ABasePickableActor::ABasePickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->SetSphereRadius(50);
	Collider->SetCollisionProfileName(FName("Pickable"));
	Collider->bGenerateOverlapEvents = true;
	Collider->SetSimulatePhysics(true);
	Collider->BodyInstance.bLockXRotation = true;
	Collider->BodyInstance.bLockYRotation = true;
	Collider->BodyInstance.bLockZRotation = false;
	Collider->BodyInstance.SetDOFLock(EDOFMode::SixDOF);

	WhereToAttach = EAttachmentPoint::AP_Overhead;
}

// Called when the game starts or when spawned
void ABasePickableActor::BeginPlay()
{
	Super::BeginPlay();
	
	FBodyInstance* body = Collider->GetBodyInstance();
	body->bLockXTranslation = true;
	body->bLockYTranslation = true;
	body->bLockZTranslation = false;
	body->SetDOFLock(EDOFMode::SixDOF);

}

void ABasePickableActor::AttachToBrawler(ACuteBrawlersCharacter * brawler)
{
	ParentBrawler = brawler;
	if (ParentBrawler)
	{
		FBodyInstance* body = Collider->GetBodyInstance();
		body->bLockXTranslation = false;
		body->bLockYTranslation = false;
		body->bLockZTranslation = false;
		ParentBrawler->AttachActor(this, WhereToAttach);
	}
}

bool ABasePickableActor::CanPickup_Implementation(ACuteBrawlersCharacter * brawler)
{
	return brawler != NULL && brawler->Stats->IsAlive();
}

void ABasePickableActor::OnPickup_Implementation(ACuteBrawlersCharacter * brawler)
{
	if (!bDestroyOnPickup && bAttachToBrawlerOnPickup)
	{
		Collider->SetSimulatePhysics(false);
		Collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		AttachToBrawler(brawler);
	}
	
}

// Called every frame
void ABasePickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ParentBrawler == NULL)
	{
		TArray<AActor*>  overlappingBrawlers;
		Collider->GetOverlappingActors(overlappingBrawlers, ACuteBrawlersCharacter::StaticClass());
		for (AActor* overlapActor : overlappingBrawlers)
		{
			ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(overlapActor);
			if (CanPickup(brawler))
			{
				OnPickup(brawler);
				if (bDestroyOnPickup)
					Destroy();
				break;
			}
		}
	}
}

