// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieEnemy.h"
#include "ZombieAIController.h"

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();

	_pNavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	//RandomPatrol();
}

void AZombieAIController::RandomPatrol()
{
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