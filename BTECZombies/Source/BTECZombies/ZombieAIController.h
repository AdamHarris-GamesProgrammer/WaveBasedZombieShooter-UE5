// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;


public:
	void PathToPlayer();

private:
	class UNavigationSystemV1* _pNavArea;

	FNavLocation _randomLocation;

	FTimerHandle _SeekPlayerTimerHandle;

};
