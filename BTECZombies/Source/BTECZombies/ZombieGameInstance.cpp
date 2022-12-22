// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UZombieGameInstance::LoadGame()
{
    // Try to load a saved game file (with name: <SaveGameSlotName>.sav) if exists
    USaveGame* LoadedGame = UGameplayStatics::LoadGameFromSlot(_saveGameSlotName, 0);
    _saveData = Cast<UZombieSaveData>(LoadedGame);

    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trying to load a saved game."));

    // If file does not exist try create a new one
    if (!_saveData)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("No saved games found. Trying to save a new one."));

        // Instantiate a new SaveGame object
        _saveData = Cast<UZombieSaveData>(UGameplayStatics::CreateSaveGameObject(UZombieSaveData::StaticClass()));

        // Call SaveGameToSlot to serialize and save our SaveGameObject with name: <SaveGameSlotName>.sav
        const bool IsSaved = UGameplayStatics::SaveGameToSlot(_saveData, _saveGameSlotName, 0);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saved game found. Loaded."));
    }

}

void UZombieGameInstance::SaveGame()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Saving game..."));

    // Call SaveGameToSlot to serialize and save our SaveGameObject with name: <SaveGameSlotName>.sav
    const bool IsSaved = UGameplayStatics::SaveGameToSlot(_saveData, _saveGameSlotName, 0);
}
