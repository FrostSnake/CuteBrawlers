// Fill out your copyright notice in the Description page of Project Settings.

#include "SideKickDummyActor.h"
#include "Components/CapsuleComponent.h"
#include "CuteBrawlersCharacter.h"


// Sets default values
ASideKickDummyActor::ASideKickDummyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bAttachToBrawler = true;
	bKillIfBrawlerDies = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->SetSphereRadius(50);
	Collider->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	Collider->bGenerateOverlapEvents = true;
}


void ASideKickDummyActor::OnInit_Implementation()
{
	Collider->IgnoreActorWhenMoving(OwningBrawler,true);
	OwningBrawler->Collider->IgnoreActorWhenMoving(this,true);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ASideKickDummyActor::OnOverlapBegin);
	SetLifeSpan(Lifetime);
}

void ASideKickDummyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == OwningBrawler)
		return;

	if (ACuteBrawlersCharacter* anotherBrawler = Cast<ACuteBrawlersCharacter>(OtherActor))
	{
		FVector dir = OtherActor->GetActorLocation() - GetActorLocation();
		dir.Normalize();
		anotherBrawler->Collider->AddImpulse(dir * KickingPower,NAME_None,true);
		
		OwningBrawler->Collider->SetAllPhysicsLinearVelocity(FVector::ZeroVector);

		Collider->OnComponentBeginOverlap.RemoveDynamic(this, &ASideKickDummyActor::OnOverlapBegin);
		Destroy();

	}

}