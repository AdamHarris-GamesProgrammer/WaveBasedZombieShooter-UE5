// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ZombieMainPlayerController.h"

void AZombieMainPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    if (_Done) return;
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    FTimerHandle handle;
    //GetWorld()->GetTimerManager().SetTimer(handle, this, &AZombieMainPlayerController::RestartLevel, 2.0, false);
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
    
    _Done = true;
}
