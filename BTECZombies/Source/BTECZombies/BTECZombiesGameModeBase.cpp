// Copyright Epic Games, Inc. All Rights Reserved.


#include "BTECZombiesGameModeBase.h"
#include "ZombiePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieEnemy.h"
#include "ZombieMainPlayerController.h"

void ABTECZombiesGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZombieSpawnPoint::StaticClass(), FoundActors);
	for (int i = 0; i < FoundActors.Num(); ++i) {
		_SpawnPoints.Add(Cast<AZombieSpawnPoint>(FoundActors[i]));
	}
	GetWorld()->GetTimerManager().SetTimer(_zombieSpawnTimerHandle, this, &ABTECZombiesGameModeBase::SpawnEnemy, 2.0f, true, 1.0f);
}

void ABTECZombiesGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ABTECZombiesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	_CurrentPoints = 0;

	_CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(GetWorld()));

	
	ChangeMenuWidget(_StartingWidgetClass);
}

void ABTECZombiesGameModeBase::SpawnEnemy()
{
	if (_SpawnPoints.Num() == 0) return;

	int randIndex = FMath::RandRange(0, _SpawnPoints.Num() - 1);

	AZombieSpawnPoint* Spawner = _SpawnPoints[randIndex];
	if (Spawner != nullptr) {
		Spawner->SpawnEnemy();
	}
}

void ABTECZombiesGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (_CurrentWidget != nullptr) {
		_CurrentWidget->RemoveFromViewport();
		_CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		_CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (_CurrentWidget != nullptr) {
			_CurrentWidget->AddToViewport();
		}
	}
}

void ABTECZombiesGameModeBase::EnemyKilled(AZombieEnemy* KilledEnemy)
{
	if (KilledEnemy == nullptr) return;

	_CurrentPoints += KilledEnemy->GetKillPoints();
}

void ABTECZombiesGameModeBase::PlayerKilled(AZombiePlayerController* KilledPlayer)
{
	//TODO: Decide on multiplayer?
	

	AZombieMainPlayerController* pc = Cast<AZombieMainPlayerController>(GetWorld()->GetFirstPlayerController());

	if (pc) {
		pc->GameHasEnded();
	}
}
