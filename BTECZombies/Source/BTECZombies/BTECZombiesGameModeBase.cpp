// Copyright Epic Games, Inc. All Rights Reserved.


#include "BTECZombiesGameModeBase.h"

void ABTECZombiesGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	GetWorld()->GetTimerManager().SetTimer(_zombieSpawnTimerHandle, this, &ABTECZombiesGameModeBase::SpawnEnemy, 5.0f, true, 5.0f);
}

void ABTECZombiesGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABTECZombiesGameModeBase::SpawnEnemy()
{

	float x = FMath::RandRange(0.0f, 3000.0f);
	float y = FMath::RandRange(0.0f, 3000.0f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector spawnLocation = FVector(x, y, 100.0f);

	GetWorld()->SpawnActor<AZombieEnemy>(_pZombieEnemy, spawnLocation,FRotator(), SpawnParams);
}
