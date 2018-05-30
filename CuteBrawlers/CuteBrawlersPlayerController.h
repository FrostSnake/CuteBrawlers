// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CuteBrawlersPlayerController.generated.h"

UCLASS()
class ACuteBrawlersPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACuteBrawlersPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void Input_Horizontal(float in_amount);
	void Input_Vertical(float in_amount);



	void Input_FaceButton_Down_Pressed();
	void Input_FaceButton_Down_Released();

	void Input_FaceButton_Left_Pressed();
	void Input_FaceButton_Left_Released();

	void Input_FaceButton_Up_Pressed();
	void Input_FaceButton_Up_Released();

	void Input_FaceButton_Right_Pressed();
	void Input_FaceButton_Right_Released();

	void Input_Shoulder_Right_Pressed();
	void Input_Shoulder_Right_Released();

	void Input_Shoulder_Left_Pressed();
	void Input_Shoulder_Left_Released();

	void Input_Trigger_Right_Pressed();
	void Input_Trigger_Right_Released();

	void Input_Trigger_Left_Pressed();
	void Input_Trigger_Left_Released();


	FVector inputVector = FVector::ZeroVector;
};


