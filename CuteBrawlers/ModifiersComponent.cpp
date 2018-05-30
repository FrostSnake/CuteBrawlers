// Fill out your copyright notice in the Description page of Project Settings.

#include "ModifiersComponent.h"
#include "AbilitiesComponent.h"
#include "CuteBrawlersCharacter.h"
#include "Engine.h"


// Sets default values for this component's properties
UModifiersComponent::UModifiersComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UModifiersComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Brawler = GetCuteBrawler();
}


// Called every frame
void UModifiersComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UModifiersComponent::AddModifier(TSubclassOf<ABaseModifier> modifierTemplate)
{
	if (modifierTemplate == NULL)
		return;

	ABaseModifier* curInstance = FindModifierOfType(modifierTemplate);
	if (curInstance != NULL && curInstance->bNonStackable)
	{
		curInstance->ResetDuration();
	}
	else
	{
		ABaseModifier* modifier = GetWorld()->SpawnActor<ABaseModifier>(modifierTemplate);
		if (modifier)
		{
			AttachedModifiers.Add(modifier);
			modifier->InitModifier(this);
		}
	}
}

void UModifiersComponent::RemoveModifier(ABaseModifier * modifier)
{
	if (modifier)
	{
		AttachedModifiers.Remove(modifier);
		modifier->Remove();
	}
}

void UModifiersComponent::RemoveModifiersOfType(TSubclassOf<ABaseModifier> modifierType)
{
	int num = AttachedModifiers.Num();
	for (int i = num - 1; i >= 0; i--)
	{
		if (AttachedModifiers[i]->GetClass() == modifierType)
		{
			AttachedModifiers[i]->Remove();
			AttachedModifiers.RemoveAt(i);
		}
	}
}

void UModifiersComponent::RemoveAllModifiers()
{
	int num = AttachedModifiers.Num();
	for (int i = num - 1; i >= 0; i--)
	{
		AttachedModifiers[i]->Remove();
	}
	AttachedModifiers.Empty();
}

void UModifiersComponent::AppendModifierEffect(EModifierEffect effect)
{
	if (effect != EModifierEffect::ME_None)
	{
		ModifierEffects.Add(effect);
		if (Brawler != NULL && effect == EModifierEffect::ME_Silenced)
		{
			Brawler->Abilities->EndCastAllAbilities();
		}
	}
}

void UModifiersComponent::RemoveModifierEffect(EModifierEffect effect)
{
	if (effect != EModifierEffect::ME_None)
		ModifierEffects.RemoveSingle(effect);
}

void UModifiersComponent::RemoveAllModifierEffectsOfType(EModifierEffect effect)
{
	if (effect != EModifierEffect::ME_None)
		ModifierEffects.Remove(effect);
}

void UModifiersComponent::RemoveAllModifierEffects()
{
	ModifierEffects.Empty();
}

bool UModifiersComponent::HasModifierEffect(EModifierEffect effect)
{
	return ModifierEffects.Find(effect) != INDEX_NONE;
}

ABaseModifier * UModifiersComponent::FindModifierOfType(TSubclassOf<ABaseModifier> modifierType)
{
	int num = AttachedModifiers.Num();
	for (int i = 0; i < num; i++)
	{
		if (AttachedModifiers[i]->GetClass() == modifierType)
		{
			return AttachedModifiers[i];
		}
	}
	return NULL;
}

ACuteBrawlersCharacter* UModifiersComponent::GetCuteBrawler()
{
	return Brawler != NULL? Brawler : Cast<ACuteBrawlersCharacter>(GetOwner());
}

