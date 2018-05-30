// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CuteBrawlersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "Materials/Material.h"
#include "AbilitiesComponent.h"
#include "ModifiersComponent.h"
#include "StatsComponent.h"
#include "Engine.h"

ACuteBrawlersCharacter::ACuteBrawlersCharacter()
{
	// Set size for player capsule
	Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitCapsuleSize(42.f, 94.0f);
	Collider->SetSimulatePhysics(true);
	Collider->BodyInstance.bLockXRotation = true;
	Collider->BodyInstance.bLockYRotation = true;
	Collider->BodyInstance.bLockZRotation = true;
	Collider->SetCollisionProfileName(FName("Pawn"));

	GroundCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("GroundCollider"));
	GroundCollider->SetupAttachment(Collider);
	GroundCollider->InitCapsuleSize(42.f, 47.0f);
	GroundCollider->SetCollisionProfileName(FName("OverlapAll"));
	GroundCollider->SetRelativeLocation(FVector(0,0,-50));


	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;




	Rotator = CreateDefaultSubobject<USceneComponent>(TEXT("Rotator"));
	Rotator->SetupAttachment(Collider);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Rotator);
	SkeletalMesh->SetCollisionProfileName(FName("NoCollision"));

	Abilities = CreateDefaultSubobject<UAbilitiesComponent>(TEXT("Abilities"));
	Abilities->SetupAttachment(GetRootComponent());

	Modifiers = CreateDefaultSubobject<UModifiersComponent>(TEXT("Modifiers"));
	Modifiers->SetupAttachment(GetRootComponent());

	BrawlerMotion = CreateDefaultSubobject<UBrawlerMotionComponent>(TEXT("BrawlerMotion"));
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));


	/***********************************Attachment Points***************************************/
	AttachmentPoint_Origin = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_Origin"));
	AttachmentPoint_Overhead = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_Overhead"));
	AttachmentPoint_Head = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_Head"));
	AttachmentPoint_LeftHand = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_LeftHand"));
	AttachmentPoint_RightHand = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_RightHand"));
	AttachmentPoint_Chest = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_Chest"));
	AttachmentPoint_LeftFoot = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_LeftFoot"));
	AttachmentPoint_RightFoot = CreateDefaultSubobject<USceneComponent>(TEXT("AttachmentPoint_RightFoot"));

	AttachmentPoint_Origin->SetupAttachment(SkeletalMesh, FName("origin"));
	AttachmentPoint_Overhead->SetupAttachment(SkeletalMesh, FName("overhead"));
	AttachmentPoint_Head->SetupAttachment(SkeletalMesh, FName("head"));
	AttachmentPoint_LeftHand->SetupAttachment(SkeletalMesh, FName("hand_left"));
	AttachmentPoint_RightHand->SetupAttachment(SkeletalMesh, FName("hand_right"));
	AttachmentPoint_Chest->SetupAttachment(SkeletalMesh, FName("chest"));
	AttachmentPoint_LeftFoot->SetupAttachment(SkeletalMesh, FName("foot_left"));
	AttachmentPoint_RightFoot->SetupAttachment(SkeletalMesh, FName("foot_right"));


	/*******************************************************************************************/


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ACuteBrawlersCharacter::BeginPlay()
{
	Super::BeginPlay();

	BrawlerMotion->SetRotatorComponent(Rotator);
	BrawlerMotion->SetGroundSensorComponent(GroundCollider);
}

void ACuteBrawlersCharacter::BeginCastAbility(int32 abilitySlotIndex)
{
	Abilities->BeginCastAbility(abilitySlotIndex);
}

void ACuteBrawlersCharacter::EndCastAbility(int32 abilitySlotIndex)
{
	Abilities->EndCastAbility(abilitySlotIndex);
}

void ACuteBrawlersCharacter::SetCollisionProfileToGhost(bool bGhost)
{
	FName profileName = bGhost ? FName("GhostPawn") : FName("Pawn");
	Collider->SetCollisionProfileName(profileName);
}

void ACuteBrawlersCharacter::SetGroundSensorCollisionProfileToGhost(bool bGhost)
{
	FName profileName = bGhost ? FName("GhostTrigger") : FName("OverlapAll");
	GroundCollider->SetCollisionProfileName(profileName);
}

void ACuteBrawlersCharacter::AttachActor(AActor * whichActor, EAttachmentPoint whichPoint)
{
	if (whichActor)
	{
		switch (whichPoint)
		{
		case EAttachmentPoint::AP_Origin:
			whichActor->AttachToComponent(AttachmentPoint_Origin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_Overhead:
			whichActor->AttachToComponent(AttachmentPoint_Overhead, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_Head:
			whichActor->AttachToComponent(AttachmentPoint_Head, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_LeftHand:
			whichActor->AttachToComponent(AttachmentPoint_LeftHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_RightHand:
			whichActor->AttachToComponent(AttachmentPoint_RightHand, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_Chest:
			whichActor->AttachToComponent(AttachmentPoint_Chest, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_LeftFoot:
			whichActor->AttachToComponent(AttachmentPoint_LeftFoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		case EAttachmentPoint::AP_RightFoot:
			whichActor->AttachToComponent(AttachmentPoint_RightFoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			break;
		}
	}
}

void ACuteBrawlersCharacter::SetModelTransparency(float transparency)
{
	UMaterialInstanceDynamic* mat = GetSkeletalMeshMaterial();
	if (mat)
	{
		mat->SetScalarParameterValue(FName("Transparency"), transparency);
	}
}

UMaterialInstanceDynamic * ACuteBrawlersCharacter::GetSkeletalMeshMaterial()
{
	if (SkeletalMeshMaterial == NULL)
	{
		SkeletalMeshMaterial = SkeletalMesh->CreateDynamicMaterialInstance(0, SkeletalMesh->GetMaterial(0));
	}
	return SkeletalMeshMaterial;
}

void ACuteBrawlersCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	//GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("%s"),BrawlerMotion->IsGrounded()?TEXT("True"):TEXT("False")));
}


