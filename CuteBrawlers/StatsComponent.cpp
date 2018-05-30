// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsComponent.h"
#include "CuteBrawlersCharacter.h"
#include "ModifiersComponent.h"


// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Brawler = Cast<ACuteBrawlersCharacter>(GetOwner());
}

void UStatsComponent::ProcessRegeneration(float DeltaTime)
{
	float hpRegen = (HitpointsRegenRate + BonusHPRegen) * DeltaTime;
	float energyRegen = (EnergyRegenRate + BonusEnergyRegen) * DeltaTime;
	Hitpoints = FMath::Min(Hitpoints + hpRegen, MaxHitpoints);
	Energy = FMath::Min(Energy + energyRegen, MaxEnergy);

}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (IsAlive())
	{
		ProcessRegeneration(DeltaTime);
	}
}

void UStatsComponent::ApplyDamage(AActor * source, float damage)
{
	if (!IsAlive() || Brawler->Modifiers->HasModifierEffect(EModifierEffect::ME_Invulnerable))
		return;

	Hitpoints = FMath::Max(Hitpoints - damage, 0.0f);
	//Do something with the source, maybe fire an event?
}

void UStatsComponent::ApplyDamageFromLocation(AActor * source, float damage, FVector worldLocation)
{
	if (!IsAlive() || Brawler->Modifiers->HasModifierEffect(EModifierEffect::ME_Invulnerable))
		return;

	ApplyDamage(source, damage);
	//Do something with the worldLocation, maybe fire another event?
}

void UStatsComponent::Heal(float amount)
{
	if (!IsAlive() || amount <= 0)
		return;

	Hitpoints = FMath::Min(Hitpoints + amount, MaxHitpoints);
	//Fire Heal Event
}

void UStatsComponent::Resurrect()
{
	if (LifeState == ELifeState::LS_Dead)
	{
		Hitpoints = MaxHitpoints;
		Energy = MaxEnergy;
		LifeState = ELifeState::LS_Alive;

		//Fire resurrect event?
	}
}

void UStatsComponent::ConsumeEnergy(float amount)
{
	if (!IsAlive() || amount <= 0)
		return;

	Energy = FMath::Max(Energy - amount, 0.0f);
	//Fire Energy Consumption event
}

void UStatsComponent::ReplenishEnergy(float amount)
{
	if (!IsAlive() || amount <= 0)
		return;

	Energy = FMath::Min(Energy + amount, MaxEnergy);
	//Fire Energy Replenished event
}

void UStatsComponent::AddBonusHPRegen(float amount)
{
	BonusHPRegen = FMath::Max(BonusHPRegen + amount, 0.0f);
}

void UStatsComponent::AddBonusEnergyRegen(float amount)
{
	BonusEnergyRegen = FMath::Max(BonusEnergyRegen + amount, 0.0f);
}

