// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BrawlerMotionComponent.h"
#include "CuteBrawlersCharacter.generated.h"

class UAbilitiesComponent;
class UStatsComponent;
class UModifiersComponent;


UENUM(BlueprintType)
enum class EAttachmentPoint : uint8
{
	//Between feet
	AP_Origin UMETA(DisplayName = "Origin"),
	//Over the head bone
	AP_Overhead UMETA(DisplayName = "Overhead"),
	//Inside the head bone
	AP_Head UMETA(DisplayName = "Head"),
	//Inside left hand bone
	AP_LeftHand UMETA(DisplayName = "LeftHand"),
	//Inside right hand bone
	AP_RightHand UMETA(DisplayName = "RightHand"),
	//Chest or center bone
	AP_Chest UMETA(DisplayName = "Chest"),
	//Inside left foot bone
	AP_LeftFoot UMETA(DisplayName = "LeftFoot"),
	//Inside right foot bone
	AP_RightFoot UMETA(DisplayName = "RightFoot")
};

UCLASS(Blueprintable)
class ACuteBrawlersCharacter : public APawn
{
	GENERATED_BODY()

public:
	ACuteBrawlersCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = CuteBrawler)
		FORCEINLINE FVector GetFacingVector() { return Rotator->GetForwardVector(); }

	UFUNCTION(BlueprintCallable, Category = Ability)
		void BeginCastAbility(int32 abilitySlotIndex);
	UFUNCTION(BlueprintCallable, Category = Ability)
		void EndCastAbility(int32 abilitySlotIndex);

	UFUNCTION(BlueprintCallable, Category = CuteBrawler)
		void SetCollisionProfileToGhost(bool bGhost);
	UFUNCTION(BlueprintCallable, Category = CuteBrawler)
		void SetGroundSensorCollisionProfileToGhost(bool bGhost);

	UFUNCTION(BlueprintCallable, Category = CuteBrawler)
		void AttachActor(AActor* whichActor, EAttachmentPoint whichPoint);

	UFUNCTION(BlueprintCallable, Category = CuteBrawler)
		void SetModelTransparency(float transparency);

	UFUNCTION(BlueprintCallable, Category = CuteBrawler)
		UMaterialInstanceDynamic* GetSkeletalMeshMaterial();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class UCapsuleComponent* Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class UCapsuleComponent* GroundCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* Rotator;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USkeletalMeshComponent* SkeletalMesh;

	UMaterialInstanceDynamic* SkeletalMeshMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class UBrawlerMotionComponent* BrawlerMotion;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class UAbilitiesComponent* Abilities;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class UModifiersComponent* Modifiers;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class UStatsComponent* Stats;

	/***********************************Attachment Points***************************************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_Origin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_Overhead;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_Head;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_LeftHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_RightHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_Chest;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_LeftFoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component)
		class USceneComponent* AttachmentPoint_RightFoot;
	/*******************************************************************************************/
};

