// Fill out your copyright notice in the Description page of Project Settings.

#include "BrawlerMotionComponent.h"
#include "Components/PrimitiveComponent.h"
#include "CuteBrawlersCharacter.h"
#include "ModifiersComponent.h"
#include "AbilitiesComponent.h"
#include "BaseAbilityComponent.h"
#include "Engine.h"


// Sets default values for this component's properties
UBrawlerMotionComponent::UBrawlerMotionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBrawlerMotionComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	SetTickGroup(ETickingGroup::TG_PrePhysics);

	Brawler = Cast<ACuteBrawlersCharacter>(GetOwner());

}

void UBrawlerMotionComponent::OnGroundSensorOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	groundOverlappingCount++;
}

void UBrawlerMotionComponent::OnGroundSensorOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	groundOverlappingCount = FMath::Max(groundOverlappingCount - 1, 0);
}

bool UBrawlerMotionComponent::IsMotionAllowed()
{
	if (Brawler)
	{
		UBaseAbilityComponent* ability = Brawler->Abilities->GetLastAbilityCast();
		if (Brawler->Abilities->IsChanneling() && ability != NULL)
		{
			return ability->bAllowMotionWhileChanneling;
		}
		return !Brawler->Modifiers->HasModifierEffect(EModifierEffect::ME_Stunned);
	}
	return true;
}

bool UBrawlerMotionComponent::IsTurningAllowed()
{
	if (Brawler)
	{
		return !Brawler->Modifiers->HasModifierEffect(EModifierEffect::ME_Stunned);
	}
	return true;
}

void UBrawlerMotionComponent::UpdateRotation(float DeltaTime)
{
	FVector vector = IsTurningAllowed() ? lastInputVector : FVector::ZeroVector;
	if (!vector.Equals(FVector::ZeroVector))
	{
		USceneComponent* comp = RotatorComponent;
		if (comp == NULL)
			comp = GetOwner()->GetRootComponent();

		comp->SetWorldRotation(FMath::RInterpTo(comp->GetComponentRotation(), lastInputVector.Rotation(), DeltaTime, TurnSpeed));
	}
}

void UBrawlerMotionComponent::DoSlipperyMotion(float DeltaTime)
{
	USceneComponent* comp = RotatorComponent;
	if (comp == NULL)
		comp = GetOwner()->GetRootComponent();

	float am = IsGrounded() ? 1 : SM_AerialMultiplier;
	FVector localVelocity = comp->GetComponentTransform().InverseTransformVector(GetOwner()->GetVelocity());
	CurrentSpeed = localVelocity.X;

	FVector vector = IsMotionAllowed() ? lastInputVector : FVector::ZeroVector;

	if (!vector.Equals(FVector::ZeroVector) && CurrentSpeed < SM_MaxSpeed * am)
	{
		
		UPrimitiveComponent* shapeComp = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		shapeComp->AddForce(comp->GetForwardVector() * SM_Acceleration * am,NAME_None,true);

	}
}

void UBrawlerMotionComponent::DoRegularMotion(float DeltaTime)
{
	float interpSpeed = Acceleration;
	float targetSpeed = IsGrounded()? MaxSpeed : (MaxSpeed * AerialMultiplier);
	FVector vector = IsMotionAllowed() ? lastInputVector : FVector::ZeroVector;


	if (vector.Equals(FVector::ZeroVector))
	{
		interpSpeed = MaxSpeed;
		targetSpeed = 0;
	}

	USceneComponent* comp = RotatorComponent;
	if (comp == NULL)
		comp = GetOwner()->GetRootComponent();

	CurrentSpeed = FMath::FInterpTo(CurrentSpeed, targetSpeed, DeltaTime, interpSpeed);

	GetOwner()->AddActorWorldOffset(comp->GetForwardVector() * CurrentSpeed * DeltaTime);
}

void UBrawlerMotionComponent::HandleImpulses(float DeltaTime)
{

	FVector accumulatedImpulses = FVector::ZeroVector;
	for (int i = 0; i < ImpulseData.Num(); i++)
	{
		FVector fractionalImpulse = ImpulseData[i].GetFractionalImpulse(DeltaTime);
		accumulatedImpulses += fractionalImpulse;
	}


	GetOwner()->AddActorWorldOffset(accumulatedImpulses);

	int num = ImpulseData.Num();
	for (int i = num-1; i >= 0; i--)
	{
		if (ImpulseData[i].bEmpty)
		{
			ImpulseData.RemoveAt(i);
		}
	}
}


// Called every frame
void UBrawlerMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	UpdateRotation(DeltaTime);

	if (bUseSlipperyMotion)
		DoSlipperyMotion(DeltaTime);
	else
		DoRegularMotion(DeltaTime);

	HandleImpulses(DeltaTime);
	
	lastInputVector = FVector::ZeroVector;
}

void UBrawlerMotionComponent::AddImpulse(FVector direction, float strength, bool oneShot, float duration)
{
	FRegularImpulseData data = FRegularImpulseData(strength, direction, oneShot, duration);
	ImpulseData.Add(data);
}

void UBrawlerMotionComponent::ClearImpulses()
{
	ImpulseData.Empty();
}

void UBrawlerMotionComponent::SetRotatorComponent(USceneComponent * newComponent)
{
	if (newComponent != NULL)
	{
		RotatorComponent = newComponent;
	}
	else
	{
		RotatorComponent = GetOwner()->GetRootComponent();
	}
}

void UBrawlerMotionComponent::SetGroundSensorComponent(UPrimitiveComponent * newComponent)
{
	if (GroundSensorComponent)
	{
		GroundSensorComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UBrawlerMotionComponent::OnGroundSensorOverlapBegin);
		GroundSensorComponent->OnComponentEndOverlap.RemoveDynamic(this, &UBrawlerMotionComponent::OnGroundSensorOverlapEnd);
	}

	GroundSensorComponent = newComponent;
	if (GroundSensorComponent)
	{

		GroundSensorComponent->OnComponentBeginOverlap.AddDynamic(this, &UBrawlerMotionComponent::OnGroundSensorOverlapBegin);
		GroundSensorComponent->OnComponentEndOverlap.AddDynamic(this, &UBrawlerMotionComponent::OnGroundSensorOverlapEnd);
		
		TArray<AActor*> currentOverlaps;
		GroundSensorComponent->GetOverlappingActors(currentOverlaps);
		groundOverlappingCount = currentOverlaps.Num();

		for (int i = 0; i < currentOverlaps.Num(); i++)
		{
			if (currentOverlaps[i] == GetOwner())
			{
				groundOverlappingCount--;
				break;
			}
		}
	}
}

void UBrawlerMotionComponent::SetInputVector(FVector inputVector)
{
	lastInputVector += inputVector;
}

