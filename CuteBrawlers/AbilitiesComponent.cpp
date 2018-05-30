// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitiesComponent.h"
#include "CuteBrawlersCharacter.h"
#include "ModifiersComponent.h"
#include "StatsComponent.h"
#include "Engine.h"


// Sets default values for this component's properties
UAbilitiesComponent::UAbilitiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	InitAbilitySlots();
}

//void UAbilitiesComponent::PostInitProperties()
//{
//	Super::PostInitProperties();
//	/*if (bRefreshListOfAbilities)
//	{
//		ListOfAbilities.Empty();
//		ListOfAbilities.AddDefaulted(8);
//		bRefreshListOfAbilities = false;
//	}*/
//}

void UAbilitiesComponent::InitAbilitySlots()
{
	int32 numOfChildren = FMath::Min(GetNumChildrenComponents(),8);
	for (int i = 0; i < numOfChildren; i++)
	{
		UBaseAbilityComponent* ability = Cast<UBaseAbilityComponent>(GetChildComponent(i));
		if (ability)
		{
			AbilitiesSlots.Add(ability);
		}
	}

	if (AbilitiesSlots.Num() < 8)
	{
		int32 dif = 8 - AbilitiesSlots.Num();
		for (int i = 0; i < dif; i++)
		{
			
			UBaseAbilityComponent* dummyAbility = NewObject<UBaseAbilityComponent>(GetOwner(), FName(*FString::Printf(TEXT("DummyAbility%d"), i)));
			if (dummyAbility)
			{
				dummyAbility->AttachToComponent(this,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				dummyAbility->RegisterComponent();
				AbilitiesSlots.Add(dummyAbility);
			}
		}
	}
	int32 numOfSlots = AbilitiesSlots.Num();
	for (int i = 0; i < numOfSlots; i++)
	{
		AttachedPickables.Add(NULL);
	}
}

void UAbilitiesComponent::ProcessAbilitySlots(float DeltaTime)
{
	int numOfSlots = AbilitiesSlots.Num();
	for (int i = numOfSlots-1; i >= 0; i--)
	{
		if (AbilitiesSlots[i]->bAbilityEnded)
		{
			ReplaceAbilityInSlot(i, UBaseAbilityComponent::StaticClass());
		}
	}
}


// Called every frame
void UAbilitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	ProcessAbilitySlots(DeltaTime);
}

void UAbilitiesComponent::BeginCastAbility(int32 abilitySlotIndex)
{
	if (!IsCastingEnabled() || abilitySlotIndex < 0 || abilitySlotIndex >= AbilitiesSlots.Num())
		return;

	if (IsChanneling())
		EndCastAllAbilities();

	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner()))
	{
		if (AbilitiesSlots[abilitySlotIndex]->BeginCast(brawler->Stats->Energy))
			brawler->Stats->ConsumeEnergy(AbilitiesSlots[abilitySlotIndex]->RequiredEnergy);
	}
}

void UAbilitiesComponent::EndCastAbility(int32 abilitySlotIndex)
{
	if (abilitySlotIndex < 0 || abilitySlotIndex >= AbilitiesSlots.Num())
		return;

	AbilitiesSlots[abilitySlotIndex]->EndCast();
}

void UAbilitiesComponent::EndCastAllAbilities()
{
	for (int i = 0; i < AbilitiesSlots.Num(); i++)
	{
		AbilitiesSlots[i]->EndCast();
	}
}

void UAbilitiesComponent::ReplaceAbilityInSlot(int32 whichSlotIndex, TSubclassOf<UBaseAbilityComponent> whichAbilityType, AActor* attachedActor)
{
	if (whichSlotIndex < 0 || whichSlotIndex >= AbilitiesSlots.Num())
	{
		if (attachedActor)
			attachedActor->Destroy();
		return;
	}

	FString abilityOriginalName = whichAbilityType.Get()->GetName();
	abilityOriginalName= abilityOriginalName.Append("%d");

	FName abilityName = FName(*FString::Printf(*abilityOriginalName,whichSlotIndex));
	UBaseAbilityComponent* newAbility = NewObject<UBaseAbilityComponent>(GetOwner(), whichAbilityType, abilityName);
	if (newAbility)
	{
		newAbility->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		newAbility->RegisterComponent();
		AbilitiesSlots[whichSlotIndex]->DestroyComponent();
		AbilitiesSlots.RemoveAt(whichSlotIndex);
		AbilitiesSlots.Insert(newAbility, whichSlotIndex);

		if (AttachedPickables[whichSlotIndex] != NULL)
		{
			AttachedPickables[whichSlotIndex]->Destroy();
		}
		AttachedPickables.RemoveAt(whichSlotIndex);
		AttachedPickables.Insert(attachedActor, whichSlotIndex);

	}
	else
	{
		if (attachedActor)
			attachedActor->Destroy();
	}
}


bool UAbilitiesComponent::IsCastingEnabled()
{
	bool result = bCastingEnabled;
	if (Brawler)
	{
		result = result && !Brawler->Modifiers->HasModifierEffect(EModifierEffect::ME_Silenced) && !Brawler->Modifiers->HasModifierEffect(EModifierEffect::ME_Stunned);
	}
	return result;
}
