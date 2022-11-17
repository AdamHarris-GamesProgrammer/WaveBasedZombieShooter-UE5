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

	

	//MaxWalkSpeed = 100.0f;
	//RandomPatrol();
}

void AZombieAIController::RandomPatrol()
{
	//TODO: REMOVE THIS LATER (Just Testing player pathing)
	PathToPlayer();
	return;

	//const FVector& Origin, float Radius, FNavLocation& ResultLocation, ANavigationData* NavData, FSharedConstNavQueryFilter QueryFilter
	AZombieEnemy* e = Cast<AZombieEnemy>(GetPawn());
	if (e && !e->IsDead) {
		if (_pNavArea) {
			if (_pNavArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, _randomLocation)) {
				MoveToLocation(_randomLocation.Location);
			}

		}
	}
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
