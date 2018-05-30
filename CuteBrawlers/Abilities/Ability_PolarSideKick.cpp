// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_PolarSideKick.h"
#include "AbilitiesComponent.h"
#include "CuteBrawlersCharacter.h"
#include "Components/CapsuleComponent.h"
#include "SideKickDummyActor.h"
#include "Engine.h"



UAbility_PolarSideKick::UAbility_PolarSideKick()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::Polarium_SideKick;
	MaxChannelingTime = 1.0f;
	bAllowMotionWhileChanneling = false;
	bOneShotAbility = true;
}

void UAbility_PolarSideKick::OnCast()
{
	Super::OnCast();
}

void UAbility_PolarSideKick::OnChannelEnd()
{
	Super::OnChannelEnd();

	float alpha = CurrentChannelingTime / MaxChannelingTime;
	UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
	FAbilityData_PolarSideKick sideKickData = abilities->AbilitiesDataAsset ? abilities->AbilitiesDataAsset->SideKick : FAbilityData_PolarSideKick::Defaults;

	float Velocity = FMath::Lerp<float>(sideKickData.MinKickVelocity, sideKickData.MaxKickVelocity, alpha);
	float Power = FMath::Lerp<float>(sideKickData.MinKickPower, sideKickData.MaxKickPower, alpha);

	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner()))
	{
		brawler->Collider->SetAllPhysicsLinearVelocity(brawler->Rotator->GetForwardVector() * Velocity);

		//Spawn a dummy actor that will push the first brawler that collides with it.
		if (sideKickData.DummyTemplate)
		{
			ASideKickDummyActor* dummy = GetWorld()->SpawnActor<ASideKickDummyActor>(sideKickData.DummyTemplate, brawler->GetActorLocation(), brawler->Rotator->GetComponentRotation());
			if (dummy)
			{
				dummy->Init(brawler);
				dummy->SetPower(Power);
			}
		}
	}
	
}