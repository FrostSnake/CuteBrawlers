// Fill out your copyright notice in the Description page of Project Settings.

#include "GhostModifier.h"
#include "ModifiersComponent.h"
#include "CuteBrawlersCharacter.h"
#include "BrawlerMotionComponent.h"


AGhostModifier::AGhostModifier()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Duration = 5.0f;
	bNonStackable = true;
	ModifierEffects.Add(EModifierEffect::ME_Invulnerable);
}

void AGhostModifier::OnModifierEffectBegan_Implementation()
{
	Super::OnModifierEffectBegan_Implementation();
	ACuteBrawlersCharacter* brawler = ModifiersContainer->GetCuteBrawler();
	brawler->SetCollisionProfileToGhost(true);
	brawler->SetGroundSensorCollisionProfileToGhost(true);
	brawler->BrawlerMotion->bUseSlipperyMotion = false;
	brawler->SetModelTransparency(GhostTransparency);
}

void AGhostModifier::OnModifierEffectEnded_Implementation()
{
	Super::OnModifierEffectEnded_Implementation();
	ACuteBrawlersCharacter* brawler = ModifiersContainer->GetCuteBrawler();
	brawler->SetCollisionProfileToGhost(false);
	brawler->SetGroundSensorCollisionProfileToGhost(false);
	brawler->BrawlerMotion->bUseSlipperyMotion = true;
	brawler->SetModelTransparency(1);
}
