// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZombieMainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API AZombieMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
		virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
	
		bool _Done = false;
};
