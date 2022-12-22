// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ZombieSaveData.h"
#include "ZombieGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API UZombieGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString _saveGameSlotName = "Save";

	UPROPERTY(BlueprintReadWrite, Category = "Settings")
	UZombieSaveData* _saveData;

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "Game Manager")
	void SaveGame();
};
