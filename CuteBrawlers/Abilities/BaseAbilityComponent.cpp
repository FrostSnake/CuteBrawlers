// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAbilityComponent.h"
#include "AbilitiesComponent.h"


// Sets default values for this component's properties
UBaseAbilityComponent::UBaseAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::NO_ABILITY;
}


// Called when the game starts
void UBaseAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!bEnabled)
		return;

	// ...
	
	if (!bOverrideDataAsset)
	{
		UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
		if (abilities->AbilitiesDataAsset)
		{
			FAbilityData_Base data = abilities->AbilitiesDataAsset->GetBaseDataByAbilityType(GetAbilityType());
			RequiredEnergy = data.RequiredEnergy;
			Cooldown = data.Cooldown;
			Charges = data.Charges;
			MaxChannelingTime = data.MaxChannelingTime;
			bAllowMotionWhileChanneling = data.bAllowMotionWhileChanneling;
			bOneShotAbility = data.bOneShotAbility;
		}
	}
}


// Called every frame
void UBaseAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bEnabled)
		return;

	// ...

	if(!IsEmptySlot())
		TickAbility(DeltaTime);
}

bool UBaseAbilityComponent::CanCast()
{
	return !IsEmptySlot() && !bAbilityBegunCast && Charges != 0 && CurrentCooldown <= 0;
}

EAbilityType UBaseAbilityComponent::GetAbilityType()
{
	return AbilityType;
}

bool UBaseAbilityComponent::BeginCast(float currentEnergy)
{
	if (!bEnabled)
		return false;

	if (!CanCast() || !HasRequiredEnergy(currentEnergy))
		return false;

	InitiateCast();
	return true;
}

void UBaseAbilityComponent::EndCast()
{
	if (!bEnabled)
		return;

	if (bAbilityBegunCast)
	{
		bAbilityBegunCast = false;
		UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
		abilities->SetIsChanneling(false);
		OnChannelEnd();
		RemoveAbilityIfOneShot();
	}
}

void UBaseAbilityComponent::OnCast()
{
}

void UBaseAbilityComponent::OnChannelEnd()
{
}

void UBaseAbilityComponent::RemoveAbilityIfOneShot()
{
	if (bOneShotAbility)
	{
		bAbilityEnded = true;
	}
}

void UBaseAbilityComponent::TickAbility(float DeltaTime)
{
	if (CurrentCooldown > 0)
	{
		CurrentCooldown -= DeltaTime;
	}
	if (bAbilityBegunCast)
	{
		if (Channel(DeltaTime))
		{
			bAbilityBegunCast = false;
			UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
			abilities->SetIsChanneling(false);
			OnChannelEnd();
			RemoveAbilityIfOneShot();
		}
	}
}
bool UBaseAbilityComponent::Channel(float DeltaTime)
{
	CurrentChannelingTime += DeltaTime;
	if (CurrentChannelingTime >= MaxChannelingTime)
		return true;
	return false;
}
void UBaseAbilityComponent::InitiateCast()
{
	CurrentCooldown = Cooldown;
	Charges = Charges >= 0 ? FMath::Max(Charges - 1, 0) : Charges;
	bAbilityBegunCast = true;
	CurrentChannelingTime = 0;

	OnCast();

	UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());

	if (MaxChannelingTime <= 0)
	{
		bAbilityBegunCast = false;
		if(Charges == 0)
			RemoveAbilityIfOneShot();
	}
	else
	{
		abilities->SetIsChanneling(true);
	}
	abilities->SetLastAbilityCast(this);
}

