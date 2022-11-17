// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombieEnemy.h"
#include "Blueprint/UserWidget.h"
#include "ZombieSpawnPoint.h"
#include "BTECZombiesGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API ABTECZombiesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	virtual void SpawnEnemy();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);


	void EnemyKilled(class AZombieEnemy* KilledEnemy);

	void PlayerKilled(class AZombiePlayerController* KilledPlayer);

	FName _CurrentLevelName;

	FTimerHandle _zombieSpawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> _StartingWidgetClass;

	UPROPERTY()
	UUserWidget* _CurrentWidget;

	TArray<AZombieSpawnPoint*> _SpawnPoints;

	UFUNCTION(BlueprintCallable)
	int GetCurrentPoints() const {
		return _CurrentPoints;
	}

	void SpendPoints(int Amount) {
		_CurrentPoints -= Amount;
	}

	int _CurrentPoints;

	int _Highscore;

};
