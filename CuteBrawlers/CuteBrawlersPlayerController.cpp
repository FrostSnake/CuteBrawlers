// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CuteBrawlersPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "CuteBrawlersCharacter.h"

ACuteBrawlersPlayerController::ACuteBrawlersPlayerController()
{

}

void ACuteBrawlersPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BrawlerMotion->SetInputVector(inputVector);
	}

	inputVector = FVector::ZeroVector;
}

void ACuteBrawlersPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("Input_Horizontal", this, &ACuteBrawlersPlayerController::Input_Horizontal);
	InputComponent->BindAxis("Input_Vertical", this, &ACuteBrawlersPlayerController::Input_Vertical);

	InputComponent->BindAction("FaceButton_Down", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_FaceButton_Down_Pressed);
	InputComponent->BindAction("FaceButton_Down", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_FaceButton_Down_Released);

	InputComponent->BindAction("FaceButton_Left", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_FaceButton_Left_Pressed);
	InputComponent->BindAction("FaceButton_Left", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_FaceButton_Left_Released);

	InputComponent->BindAction("FaceButton_Up", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_FaceButton_Up_Pressed);
	InputComponent->BindAction("FaceButton_Up", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_FaceButton_Up_Released);

	InputComponent->BindAction("FaceButton_Right", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_FaceButton_Right_Pressed);
	InputComponent->BindAction("FaceButton_Right", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_FaceButton_Right_Released);
	
	InputComponent->BindAction("Shoulder_Right", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_Shoulder_Right_Pressed);
	InputComponent->BindAction("Shoulder_Right", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_Shoulder_Right_Released);
	
	InputComponent->BindAction("Shoulder_Left", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_Shoulder_Left_Pressed);
	InputComponent->BindAction("Shoulder_Left", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_Shoulder_Left_Released);
	
	InputComponent->BindAction("Trigger_Right", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_Trigger_Right_Pressed);
	InputComponent->BindAction("Trigger_Right", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_Trigger_Right_Released);
	
	InputComponent->BindAction("Trigger_Left", EInputEvent::IE_Pressed, this, &ACuteBrawlersPlayerController::Input_Trigger_Left_Pressed);
	InputComponent->BindAction("Trigger_Left", EInputEvent::IE_Released, this, &ACuteBrawlersPlayerController::Input_Trigger_Left_Released);


}

void ACuteBrawlersPlayerController::Input_Horizontal(float in_amount)
{
	inputVector.Y = in_amount;
}
void ACuteBrawlersPlayerController::Input_Vertical(float in_amount)
{
	inputVector.X = in_amount;
}

void ACuteBrawlersPlayerController::Input_FaceButton_Down_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(0);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Down_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(0);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Left_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(1);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Left_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(1);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Up_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(2);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Up_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(2);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Right_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(3);
	}
}

void ACuteBrawlersPlayerController::Input_FaceButton_Right_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(3);
	}
}

void ACuteBrawlersPlayerController::Input_Shoulder_Right_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(4);
	}
}

void ACuteBrawlersPlayerController::Input_Shoulder_Right_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(4);
	}
}

void ACuteBrawlersPlayerController::Input_Shoulder_Left_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(5);
	}
}

void ACuteBrawlersPlayerController::Input_Shoulder_Left_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(5);
	}
}

void ACuteBrawlersPlayerController::Input_Trigger_Right_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(6);
	}
}

void ACuteBrawlersPlayerController::Input_Trigger_Right_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(6);
	}
}

void ACuteBrawlersPlayerController::Input_Trigger_Left_Pressed()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->BeginCastAbility(7);
	}
}

void ACuteBrawlersPlayerController::Input_Trigger_Left_Released()
{
	if (ACuteBrawlersCharacter* brawler = Cast<ACuteBrawlersCharacter>(GetPawn()))
	{
		brawler->EndCastAbility(7);
	}
}
