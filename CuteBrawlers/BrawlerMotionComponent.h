// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "BrawlerMotionComponent.generated.h"

USTRUCT(BlueprintType)
struct FRegularImpulseData
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, Category = Default)
		float ImpulseStrength;
	UPROPERTY(VisibleAnywhere, Category = Default)
		float FullTime;
	UPROPERTY(VisibleAnywhere, Category = Default)
		float RemainingTime;
	UPROPERTY(VisibleAnywhere, Category = Default)
		bool bOneShot;
	UPROPERTY(VisibleAnywhere, Category = Default)
		FVector ImpulseDirection;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Default)
		bool bEmpty;

	FRegularImpulseData(float impulse, FVector dir, bool isOneShot, float time = 0.5f)
	{
		ImpulseStrength = impulse;
		ImpulseDirection = dir;
		bOneShot = isOneShot;
		FullTime = RemainingTime = time;
		bEmpty = false;
	}
	FRegularImpulseData()
	{
		ImpulseStrength = 0;
		ImpulseDirection = FVector::ZeroVector;
		bOneShot = true;
		FullTime = RemainingTime = 0;
		bEmpty = false;
	}


	FVector GetFractionalImpulse(float deltaTime)
	{
		if (bEmpty || deltaTime == 0)
			return FVector::ZeroVector;

		FVector impulse = ImpulseDirection;
		if (bOneShot)
		{
			impulse *= ImpulseStrength;
			bEmpty = true;
		}
		else
		{
			float step = FMath::Max(FullTime / deltaTime,1.f);
			float fractionImpulse = ImpulseStrength / step;
			impulse *=fractionImpulse;

			RemainingTime -= deltaTime;
			if (RemainingTime <= 0)
				bEmpty = true;
		}
		return impulse;
	}
};

class ACuteBrawlersCharacter;

UCLASS( ClassGroup=(CuteBrawler), meta=(BlueprintSpawnableComponent) )
class CUTEBRAWLERS_API UBrawlerMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBrawlerMotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnGroundSensorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnGroundSensorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	bool IsMotionAllowed();
	bool IsTurningAllowed();

	void UpdateRotation(float DeltaTime);
	void DoSlipperyMotion(float DeltaTime);
	void DoRegularMotion(float DeltaTime);
	void HandleImpulses(float DeltaTime);



	FVector lastInputVector = FVector::ZeroVector;
	int groundOverlappingCount = 0;
	ACuteBrawlersCharacter* Brawler;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Motion)
		void AddImpulse(FVector direction, float strength, bool oneShot, float duration = 0);
	UFUNCTION(BlueprintCallable, Category = Motion)
		void ClearImpulses();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Motion)
		FORCEINLINE bool IsGrounded()
		{
			return groundOverlappingCount > 0;
		}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Motion)
	FORCEINLINE float GetMaxSpeed()
	{
		return bUseSlipperyMotion? SM_MaxSpeed : MaxSpeed;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Motion)
		float CurrentSpeed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion)
		float TurnSpeed = 10;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion)
		float MaxSpeed = 350;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion)
		float Acceleration = 70;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion, Meta = (ClampMin = "0", ClampMax = "1"))
		float AerialMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Motion)
		bool bUseSlipperyMotion = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion|SlipperyMotion", Meta = (EditCondition = bUseSlipperyMotion))
		float SM_MaxSpeed = 750;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion|SlipperyMotion", Meta = (EditCondition = bUseSlipperyMotion))
		float SM_Acceleration = 700;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Motion|SlipperyMotion", Meta = (EditCondition = bUseSlipperyMotion, ClampMin = "0", ClampMax = "1"))
		float SM_AerialMultiplier = 0.5f;

	UPROPERTY()
		TArray<FRegularImpulseData> ImpulseData;

	UPROPERTY(BlueprintReadOnly, Category = Motion)
		USceneComponent* RotatorComponent;
	UPROPERTY(BlueprintReadOnly, Category = Motion)
		UPrimitiveComponent* GroundSensorComponent;

	UFUNCTION(BlueprintCallable, Category = Motion)
		void SetRotatorComponent(USceneComponent* newComponent);
	UFUNCTION(BlueprintCallable, Category = Motion)
		void SetGroundSensorComponent(UPrimitiveComponent* newComponent);
	UFUNCTION(BlueprintCallable, Category = Motion)
		void SetInputVector(FVector inputVector);
	
};

