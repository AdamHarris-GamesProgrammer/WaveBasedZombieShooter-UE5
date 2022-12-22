// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ZombieSaveData.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API UZombieSaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UZombieSaveData();

	UPROPERTY(BlueprintReadWrite, Category = "Game Settings")
	float _sfxVolume = 1.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Game Settings")
	float _musicVolume = 1.0f;


	
};
