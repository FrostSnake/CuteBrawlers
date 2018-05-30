// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability_PolarThrowBoomerang.h"
#include "AbilitiesDataAsset.h"
#include "CuteBrawlersCharacter.h"
#include "AbilitiesComponent.h"
#include "Engine.h"
#include "BoomerangProjectile.h"



UAbility_PolarThrowBoomerang::UAbility_PolarThrowBoomerang()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AbilityType = EAbilityType::Polarium_ThrowBoomerang;
}

void UAbility_PolarThrowBoomerang::OnCast()
{
	Super::OnCast();

	UAbilitiesComponent* abilities = Cast<UAbilitiesComponent>(GetAttachParent());
	FAbilityData_PolarBoomerang boomerangData;
	boomerangData = abilities->AbilitiesDataAsset ? abilities->AbilitiesDataAsset->ThrowBoomerang : FAbilityData_PolarBoomerang::Defaults;

	if (boomerangData.ProjectileTemplate)
	{
		if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetOwner()))
		{
			ABoomerangProjectile* proj = GetWorld()->SpawnActor<ABoomerangProjectile>(boomerangData.ProjectileTemplate, brawler->GetActorLocation(), brawler->Rotator->GetComponentRotation());
			proj->SetOwner(brawler);
			proj->Launch();
		}
	}

}