// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickable_Ability.h"
#include "BaseAbilityComponent.h"
#include "CuteBrawlersCharacter.h"
#include "AbilitiesComponent.h"

APickable_Ability::APickable_Ability()
{
	AbilityToAdd = NULL;
	AbilitySlotIndex = 2;
}

bool APickable_Ability::CanPickup_Implementation(ACuteBrawlersCharacter * brawler)
{
	return Super::CanPickup_Implementation(brawler) && brawler->Abilities->AbilitiesSlots[AbilitySlotIndex]->IsEmptySlot();
}

void APickable_Ability::OnPickup_Implementation(ACuteBrawlersCharacter * brawler)
{
	Super::OnPickup_Implementation(brawler);

	brawler->Abilities->ReplaceAbilityInSlot(AbilitySlotIndex, AbilityToAdd,this);
}
