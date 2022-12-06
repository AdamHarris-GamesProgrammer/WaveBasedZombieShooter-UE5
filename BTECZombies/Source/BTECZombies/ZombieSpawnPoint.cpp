// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieAIController.h"
#include "ZombieSpawnPoint.h"
#include "BTECZombiesGameModeBase.h"

// Sets default values
AZombieSpawnPoint::AZombieSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AZombieSpawnPoint::ActivateSpawn()
{
	if (_SpawnPointActive) return;

	ABTECZombiesGameModeBase* gm = Cast< ABTECZombiesGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gm) {
		gm->AddActiveSpawnPoint(this);
	}
	_SpawnPointActive = true;
}

// Called when the game starts or when spawned
void AZombieSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AZombieSpawnPoint::SpawnEnemy()
{
	if (!_SpawnPointActive) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	int index = FMath::RandRange(0, _EnemyVarities.Num() - 1);

	FVector spawnPos = GetActorLocation();
	spawnPos.Z += 100.0f;

	AZombieEnemy* enemy = GetWorld()->SpawnActor<AZombieEnemy>(_EnemyVarities[index], spawnPos, FRotator(), SpawnParams);

	if (enemy) {
		AZombieAIController* ai = Cast<AZombieAIController>(enemy->GetController());
		if (ai) {
			//ai->PathToPlayer();
		}
	}
}

