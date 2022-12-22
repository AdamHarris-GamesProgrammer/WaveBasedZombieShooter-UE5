// Copyright Epic Games, Inc. All Rights Reserved.


#include "BTECZombiesGameModeBase.h"
#include "ZombiePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieEnemy.h"
#include "ZombieSpawnPoint.h"
#include "ZombieMainPlayerController.h"
#include "ZombieWindow.h"
#include "RoomVolume.h"
#include "ZombieSaveData.h"
#include "ZombieRoom.h"
#include "ZombieGameInstance.h"

void ABTECZombiesGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UWorld* World = GetWorld();

	TArray<AActor*> rooms;
	UGameplayStatics::GetAllActorsOfClass(World, AZombieRoom::StaticClass(), rooms);

	for (int i = 0; i < rooms.Num(); ++i) {
		AZombieRoom* r = Cast<AZombieRoom>(rooms[i]);
		//r->LoadStartAttributes();
	}

	for (int i = 0; i < rooms.Num(); ++i) {
		AZombieRoom* r = Cast <AZombieRoom>(rooms[i]);
		r->LoadEndAttributes();
	}
		
	for (int i = 0; i < rooms.Num(); ++i) {
		AZombieRoom* r = Cast <AZombieRoom>(rooms[i]);
		if (r) {
			if (r->ActivateOnBeginPlay()) {
				r->ActivateRoom();
			}
		}
	}

	_RemainingZombiesToSpawn = _StartingAmountOfZombies;

	GetWorld()->GetTimerManager().SetTimer(_RoundTransitionTimerHandle, this, &ABTECZombiesGameModeBase::StartNewRound, _TimeBetweenRounds, false);

	UGameInstance* gi = UGameplayStatics::GetGameInstance(GetWorld());
	UZombieGameInstance* zgi = Cast<UZombieGameInstance>(gi);

	if (zgi) {
		zgi->LoadGame();
		_saveData = zgi->_saveData;

		_sfxVolume = _saveData->_sfxVolume;
		_musicVolume = _saveData->_musicVolume;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Game Instance not acquired"));
	}

	if (_MapAmbienceMusic) {
		UGameplayStatics::PlaySound2D(GetWorld(), _MapAmbienceMusic, 0.15f * _musicVolume, 1.0f, 0.0f);
	}
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

	if (_RemainingZombiesToSpawn <= 0) return;

	//Get the player
	//Get the past three rooms the player has been in and get the windows attached to it
	//Get all the spawn points attached to those windows
	//Choose a spawn point out of those

	AZombiePlayerController* pc = Cast<AZombiePlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (pc) {
		TArray<AZombieRoom*> rooms = pc->GetRooms();

		if (rooms.Num() != 0) {
			TArray<AZombieWindow*> windowsAvailable;
			for (auto* r : rooms) {
				windowsAvailable.Append(r->GetWindows());
			}

			if (windowsAvailable.Num() != 0) {
				TArray<AZombieSpawnPoint*> spawners;
				for (auto* w : windowsAvailable) {
					if (!w->IsActivated()) continue;
					spawners.Append(w->GetSpawnPoints());
				}

				if (spawners.Num() == 0) {
					UE_LOG(LogTemp, Warning, TEXT("No Spawners"));
				}

				int randIndex = FMath::RandRange(0, spawners.Num() - 1);

				AZombieSpawnPoint* Spawner = spawners[randIndex];
				if (Spawner != nullptr) {
					Spawner->SpawnEnemy();
				}

				_RemainingZombiesToSpawn--;
				_RemainingZombiesAlive++;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("No windows"));
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("No rooms"));
		}
	}
}

void ABTECZombiesGameModeBase::StartNewRound()
{
	if (_RoundBeginSFX) {
		UGameplayStatics::PlaySound2D(GetWorld(), _RoundBeginSFX, 1.0f * _sfxVolume);
	}

	_CurrentRound++;

	UE_LOG(LogTemp, Warning, TEXT("Round: %i"), _CurrentRound);

	//Compounding Interest Formula
	//A = P(1 + r/n)^nt 
	//A: Amount P: Principal R: Interest Rate N: Number of times interest is compounded per T T: Time (current round in this case)
	_RemainingZombiesToSpawn = _StartingAmountOfZombies * FMath::Pow((1 + _PercentageIncrease / 1), 1 * _CurrentRound);

	UE_LOG(LogTemp, Warning, TEXT("This round will have: %i"), _RemainingZombiesToSpawn);

	GetWorld()->GetTimerManager().SetTimer(_zombieSpawnTimerHandle, this, &ABTECZombiesGameModeBase::SpawnEnemy, 2.0f, true, 1.0f);
	_TransitioningToNextRound = false;
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

	_RemainingZombiesAlive--;

	//No more zombies to spawn and no more zombies alive
	if (_RemainingZombiesToSpawn == 0 && _RemainingZombiesAlive <= 0) {
		_TransitioningToNextRound = true;
		GetWorld()->GetTimerManager().SetTimer(_RoundTransitionTimerHandle, this, &ABTECZombiesGameModeBase::StartNewRound, _TimeBetweenRounds, false);
		GetWorld()->GetTimerManager().ClearTimer(_zombieSpawnTimerHandle);
	}

	_CurrentPoints += KilledEnemy->GetKillPoints();
	//UE_LOG(LogTemp, Warning, TEXT("Current Points: %i"), _CurrentPoints);
}

void ABTECZombiesGameModeBase::PlayerKilled(AZombiePlayerController* KilledPlayer)
{
	//TODO: Decide on multiplayer?
	
	AZombieMainPlayerController* pc = Cast<AZombieMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (pc) {
		pc->GameHasEnded();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not found"));
	}
}

void ABTECZombiesGameModeBase::AddActiveSpawnPoint(AZombieSpawnPoint* Spawn)
{
	_SpawnPoints.Add(Spawn);
}
