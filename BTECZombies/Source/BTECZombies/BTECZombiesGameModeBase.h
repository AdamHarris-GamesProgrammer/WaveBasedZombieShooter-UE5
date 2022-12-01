// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ZombieEnemy.h"
#include "Blueprint/UserWidget.h"
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

	UFUNCTION(BlueprintCallable)
	int GetCurrentPoints() const {
		return _CurrentPoints;
	}

	bool CanAfford(int Amount) {
		if (!_SpendMoney) return true;

		return Amount <= _CurrentPoints;
	}

	void SpendPoints(int Amount) {
		if (!_SpendMoney) return;

		//UE_LOG(LogTemp, Warning, TEXT("Amount to Spend: %i"), Amount);
		_CurrentPoints -= Amount;
		//UE_LOG(LogTemp, Warning, TEXT("Remaining Points: %i"), _CurrentPoints);
	}

	void AddActiveSpawnPoint(class AZombieSpawnPoint* Spawn);

protected:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUserWidget> _StartingWidgetClass;

	UPROPERTY()
	UUserWidget* _CurrentWidget;

	TArray<class AZombieSpawnPoint*> _SpawnPoints;

	UPROPERTY(EditAnywhere)
	bool _SpendMoney = true;
private:
	int _CurrentPoints = 0;
	int _Highscore = 0;


	FName _CurrentLevelName = "";
	FTimerHandle _zombieSpawnTimerHandle;
};
