// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieMainPlayerController.h"

void AZombieMainPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    //RestartLevel();
}
