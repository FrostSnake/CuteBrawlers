// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_PolarThrowBoulder.h"
#include "Polarium_Boulder.h"
#include "AbilitiesComponent.h"
#include "CuteBrawlersCharacter.h"
#include "Engine.h"


UAbility_PolarThrowBoulder::UAbility_PolarThrowBoulder()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::Polarium_ThrowBoulder;
	Cooldown = 5.0f;
	MaxChannelingTime = 1.0f;
	bOneShotAbility = true;
}

void UAbility_PolarThrowBoulder::OnCast()
{
	Super::OnCast();
}

void UAbility_PolarThrowBoulder::OnChannelEnd()
{
	Super::OnChannelEnd();

	float alpha = CurrentChannelingTime / MaxChannelingTime;
	UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
	FAbilityData_ThrowBoulder boulderData = abilities ->AbilitiesDataAsset? abilities->AbilitiesDataAsset->ThrowBoulder : FAbilityData_ThrowBoulder::Defaults;

	if (boulderData.TemplateBoulder)
	{
		if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner()))
		{
			FRotator rot = brawler->Rotator->GetForwardVector().Rotation();
			rot.Add(boulderData.ThrowAngle, 0, 0);
			float speed = FMath::Lerp<float>(boulderData.MinThrowSpeed, boulderData.MaxThrowSpeed, alpha);
			APolarium_Boulder* boulder = GetWorld()->SpawnActor<APolarium_Boulder>(boulderData.TemplateBoulder, brawler->GetActorLocation() + FVector::UpVector * 200, rot);
			boulder->Launch(speed);
		}
	}
}

