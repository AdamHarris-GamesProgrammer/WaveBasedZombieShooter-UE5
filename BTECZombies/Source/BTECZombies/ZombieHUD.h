// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "ZombieHUD.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API AZombieHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

protected:

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* _pCrosshairTexture;
	
};
