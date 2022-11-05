// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieAIController.h"

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	_pNavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	RandomPatrol();
}

void AZombieAIController::RandomPatrol()
{
	if (_pNavArea) {
		_pNavArea->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(), _randomLocation, 15000.0f);

		MoveToLocation(_randomLocation);
	}
}
