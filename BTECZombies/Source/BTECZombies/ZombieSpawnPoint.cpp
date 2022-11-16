// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSpawnPoint.h"

// Sets default values
AZombieSpawnPoint::AZombieSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieSpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	int index = FMath::RandRange(0, _EnemyVarities.Num() - 1);

	FVector spawnPos = GetActorLocation();
	spawnPos.Z += 200.0f;

	AZombieEnemy* enemy = GetWorld()->SpawnActor<AZombieEnemy>(_EnemyVarities[index], spawnPos, FRotator(), SpawnParams);

	if (enemy) {
		AZombieAIController* ai = Cast<AZombieAIController>(enemy->GetController());
		if (ai) {
			//ai->PathToPlayer();
		}
	}
}

