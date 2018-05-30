// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_ApplyModifier.h"
#include "CuteBrawlersCharacter.h"
#include "ModifiersComponent.h"

UAbility_ApplyModifier::UAbility_ApplyModifier()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::NO_ABILITY;
	OverridenAbilityType = EAbilityType::NO_ABILITY;
}

EAbilityType UAbility_ApplyModifier::GetAbilityType()
{
	return OverridenAbilityType;
}

void UAbility_ApplyModifier::PostInitProperties()
{
	Super::PostInitProperties();

	AbilityType = OverridenAbilityType;
}

void UAbility_ApplyModifier::BeginPlay()
{
	Super::BeginPlay();

	AbilityType = OverridenAbilityType;
}


void UAbility_ApplyModifier::OnCast()
{
	int num = ListOfModifiers.Num();
	if (num <= 0)
		return;

	ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner());
	if (brawler)
	{
		for (int i = 0; i < num; i++)
		{
			brawler->Modifiers->AddModifier(ListOfModifiers[i]);
		}
	}
}
