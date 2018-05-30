// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseModifier.h"
#include "ModifiersComponent.h"


// Sets default values
ABaseModifier::ABaseModifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseModifier::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseModifier::OnModifierEffectBegan_Implementation()
{

}

void ABaseModifier::OnModifierEffectEnded_Implementation()
{

}

void ABaseModifier::OnModifierTimeEnded()
{
	ModifiersContainer->RemoveModifier(this);
}

// Called every frame
void ABaseModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (ModifiersContainer == NULL)
		return;

	if (TimeLeft > 0)
	{
		TimeLeft -= DeltaTime;
		if (TimeLeft <= 0)
		{
			OnModifierTimeEnded();
		}
	}

}

void ABaseModifier::InitModifier(UModifiersComponent * container)
{
	ModifiersContainer = container;
	AttachToComponent(ModifiersContainer, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	ResetDuration();
	
	int num = ModifierEffects.Num();
	for (int i = 0; i < num; i++)
	{
		ModifiersContainer->AppendModifierEffect(ModifierEffects[i]);
	}
	
	OnModifierEffectBegan();
}

void ABaseModifier::Remove()
{
	int num = ModifierEffects.Num();
	for (int i = 0; i < num; i++)
	{
		ModifiersContainer->RemoveModifierEffect(ModifierEffects[i]);
	}

	OnModifierEffectEnded();

	Destroy();
}

void ABaseModifier::SetCustomDuration(float newDuration)
{
	TimeLeft = newDuration;
}

void ABaseModifier::ResetDuration()
{
	TimeLeft = Duration;
}

