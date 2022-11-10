// Copyright Epic Games, Inc. All Rights Reserved.


#include "BTECZombiesGameModeBase.h"

void ABTECZombiesGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GetWorld()->GetTimerManager().SetTimer(_zombieSpawnTimerHandle, this, &ABTECZombiesGameModeBase::SpawnEnemy, 2.0f, true, 1.0f);
}

void ABTECZombiesGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABTECZombiesGameModeBase::SpawnEnemy()
{

	float x = FMath::RandRange(-500.0f, -2500.0f);
	float y = FMath::RandRange(-2000.0f, 2000.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector spawnLocation = FVector(x, y, 190.0f);

	AZombieEnemy* enemy = GetWorld()->SpawnActor<AZombieEnemy>(_pZombieEnemy, spawnLocation,FRotator(), SpawnParams);
	
	if (enemy) {
		AZombieAIController* ai = Cast<AZombieAIController>(enemy->GetController());
		if (ai) {
			ai->PathToPlayer();
		}
	}
	
}
