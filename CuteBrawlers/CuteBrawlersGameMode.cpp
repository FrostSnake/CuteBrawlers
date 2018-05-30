// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CuteBrawlersGameMode.h"
#include "CuteBrawlersPlayerController.h"
#include "CuteBrawlersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

ACuteBrawlersGameMode::ACuteBrawlersGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACuteBrawlersPlayerController::StaticClass();
}


void ACuteBrawlersGameMode::StartPlay()
{
	if (NumOfLocalPlayers > 1)
	{
		for (int i = 0; i < NumOfLocalPlayers - 1; i++)
		{
			UGameplayStatics::CreatePlayer(GetWorld());
		}
	}

	Super::StartPlay();
}