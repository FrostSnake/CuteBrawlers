// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Polarium_Boulder.h"
#include "AbilitiesDataAsset.generated.h"

class ABaseProjectile;
class ABoomerangProjectile;
class AGhostModifier;
class ASpawnAbilityActor;
class ASideKickDummyActor;

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	NO_ABILITY = 0,
	Polarium_TestJump = 1,
	Polarium_PolarDash = 2,
	Polarium_ThrowBoulder = 3,
	Polarium_ThrowBoomerang = 4,
	Polarium_BecomeGhost = 5,
	Polarium_Whirlwind = 6,
	Polarium_SideKick = 7
};

USTRUCT(BlueprintType)
struct FAbilityData_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = "0"))
		//The amount of energy points needed to cast the ability.
		float RequiredEnergy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = "0"))
		//Time until the ability can be used again after a successful cast.
		float Cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = "0"))
		//The maximum channeling time, if the ability needs it.
		float MaxChannelingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		//If false, the brawler will be unable to move while channeling (turning is unaffected though)
		bool bAllowMotionWhileChanneling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = "-1"))
		//Number of charges the ability have. Negative value indicates infinite charges.
		int32 Charges;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		//If true, the ability will be removed from the ability slot after a successful cast.
		bool bOneShotAbility;
	FAbilityData_Base()
	{
		RequiredEnergy = 0;
		Cooldown = 0;
		MaxChannelingTime = 0;
		bAllowMotionWhileChanneling = true;
		Charges = -1;
		bOneShotAbility = false;
	}
};


USTRUCT(BlueprintType)
struct FAbilityData_PolarDash : public FAbilityData_Base
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		//The amount of energy points needed to cast the ability.
		float DashStrength;

	FAbilityData_PolarDash()
	{
		DashStrength = 500.f;
	}

	static FAbilityData_PolarDash Defaults;
};

USTRUCT(BlueprintType)
struct FAbilityData_ThrowBoulder : public FAbilityData_Base
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = 0))
		float MinThrowSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = 0))
		float MaxThrowSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = -90, ClampMax = 90))
		float ThrowAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TSubclassOf<APolarium_Boulder> TemplateBoulder;
	FAbilityData_ThrowBoulder()
	{
		MinThrowSpeed = 350.0f;
		MaxThrowSpeed = 750.0f;
		MaxChannelingTime = 2.0f;
		bAllowMotionWhileChanneling = true;
		ThrowAngle = 45.0f;
		TemplateBoulder = NULL;
	}
	static FAbilityData_ThrowBoulder Defaults;

};

USTRUCT(BlueprintType)
struct FAbilityData_PolarBoomerang : public FAbilityData_Base
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TSubclassOf<ABoomerangProjectile> ProjectileTemplate;

	FAbilityData_PolarBoomerang()
	{
		ProjectileTemplate = NULL;
		bAllowMotionWhileChanneling = true;
	}

	static FAbilityData_PolarBoomerang Defaults;
};

USTRUCT(BlueprintType)
struct FAbilityData_PolarGhost : public FAbilityData_Base
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TSubclassOf<AGhostModifier> ModifierTemplate;

	FAbilityData_PolarGhost()
	{
		ModifierTemplate = NULL;
		bAllowMotionWhileChanneling = true;
	}

	static FAbilityData_PolarGhost Defaults;
};

USTRUCT(BlueprintType)
struct FAbilityData_PolarWhirlwind : public FAbilityData_Base
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TSubclassOf<ASpawnAbilityActor> ActorTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		float MinStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		float MaxStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability, Meta = (ClampMin = 0))
		float Duration;

	FAbilityData_PolarWhirlwind()
	{
		ActorTemplate = NULL;
		MinStrength = 600;
		MaxStrength = 1500;
		Duration = 3;
		bAllowMotionWhileChanneling = true;
	}

	static FAbilityData_PolarWhirlwind Defaults;
};

USTRUCT(BlueprintType)
struct FAbilityData_PolarSideKick : public FAbilityData_Base
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		float MinKickPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		float MaxKickPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		float MinKickVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		float MaxKickVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ability)
		TSubclassOf<ASideKickDummyActor> DummyTemplate;

	FAbilityData_PolarSideKick()
	{
		MinKickPower = 2000;
		MaxKickPower = 3500;
		MinKickVelocity = 500;
		MaxKickVelocity = 1000;
		DummyTemplate = NULL;
		MaxChannelingTime = 1.0f;
		bAllowMotionWhileChanneling = false;
	}

	static FAbilityData_PolarSideKick Defaults;
};

/**
 * 
 */
UCLASS(Blueprintable)
class CUTEBRAWLERS_API UAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Polarium")
		FAbilityData_PolarDash PolarDash;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Polarium")
		FAbilityData_ThrowBoulder ThrowBoulder;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Polarium")
		FAbilityData_PolarBoomerang ThrowBoomerang;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Polarium")
		FAbilityData_PolarGhost BecomeGhost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Polarium")
		FAbilityData_PolarWhirlwind SpawnWhirlwind;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability|Polarium")
		FAbilityData_PolarSideKick SideKick;

	FAbilityData_Base GetBaseDataByAbilityType(EAbilityType abilityType)
	{
		switch (abilityType)
		{
		case EAbilityType::NO_ABILITY:
			break;
		case EAbilityType::Polarium_TestJump:
			break;
		case EAbilityType::Polarium_PolarDash:
			return PolarDash;
			break;
		case EAbilityType::Polarium_ThrowBoulder:
			return ThrowBoulder;
			break;
		case EAbilityType::Polarium_ThrowBoomerang:
			return ThrowBoomerang;
			break;
		case EAbilityType::Polarium_BecomeGhost:
			return BecomeGhost;
			break;
		case EAbilityType::Polarium_Whirlwind:
			return SpawnWhirlwind;
			break;
		case EAbilityType::Polarium_SideKick:
			return SideKick;
			break;
		default:
			break;
		}
		return FAbilityData_Base();
	}
};
