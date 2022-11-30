// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieEnemy.h"
#include "ZombieSpawnPoint.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieSpawnPoint();

	void ActivateSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AZombieEnemy>> _EnemyVarities;

	void SpawnEnemy();

private:
	bool _SpawnPointActive = false;

};
