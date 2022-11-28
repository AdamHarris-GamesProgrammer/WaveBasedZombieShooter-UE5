// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieEnemy.h"

#include "ZombieAIController.h"
#include "GameFramework/Character.h"
#include <Kismet/GameplayStatics.h>

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	_pNavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	GetWorld()->GetTimerManager().SetTimer(_SeekPlayerTimerHandle, this, &AZombieAIController::PathToPlayer, 1.0f, true, 0.0f);
}

void AZombieAIController::PathToPlayer()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc != nullptr) {
		if (pc->GetPawn() == nullptr) return;

		MoveToLocation(pc->GetPawn()->GetActorLocation());
		SetFocus(pc->GetPawn());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to path to Player!"));
	}
}
