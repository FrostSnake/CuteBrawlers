// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_PolarDash.h"
#include "AbilitiesDataAsset.h"
#include "CuteBrawlersCharacter.h"
#include "AbilitiesComponent.h"

UAbility_PolarDash::UAbility_PolarDash()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::Polarium_PolarDash;
	Cooldown = 2.0f;
}

void UAbility_PolarDash::OnCast()
{
	Super::OnCast();
	
	UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
	FAbilityData_PolarDash polarData;
	polarData = abilities->AbilitiesDataAsset? abilities->AbilitiesDataAsset->PolarDash : FAbilityData_PolarDash::Defaults;
	
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner()))
	{
		if (UPrimitiveComponent* rb = Cast<UPrimitiveComponent>(brawler->GetRootComponent()))
		{
			rb->AddImpulse(brawler->Rotator->GetForwardVector() * polarData.DashStrength,NAME_None, true);
		}
	}

}
