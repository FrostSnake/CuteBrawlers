// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CuteBrawlersGameMode.generated.h"

UCLASS(minimalapi)
class ACuteBrawlersGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void StartPlay() override;

public:
	ACuteBrawlersGameMode();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CuteBrawlersGameMode, Meta = (ClampMin = "1", ClampMax = "6"))
		int32 NumOfLocalPlayers = 2;
};



