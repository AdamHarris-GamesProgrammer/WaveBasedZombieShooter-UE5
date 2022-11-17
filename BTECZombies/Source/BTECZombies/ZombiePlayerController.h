// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "GameFramework/PlayerController.h"

#include "ZombieWeapon.h"
#include "ZombiePlayerController.generated.h"



UCLASS()
class BTECZOMBIES_API AZombiePlayerController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombiePlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void SetNearbyWindow(class AZombieWindow* window) { _NearbyWindow = window; }

	//Handles moving forward and backward
	UFUNCTION() //Adding UFUNCTION macro means that the engine is aware of these functions and will be included in serialization
	void MoveForward(float value);

	//Handles moving right and left
	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void Turn(float value);

	UFUNCTION()
	void LookUp(float value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Reload();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage() {
		return _currentHealth / _maxHealth;
	}

	UFUNCTION(BlueprintCallable)
	FString GetHealthText() {
		FString val = FString::SanitizeFloat(_currentHealth, 0) + "/" + FString::SanitizeFloat(_maxHealth, 0);
		return val;
	}

	UFUNCTION(BlueprintCallable)
	AZombieWeapon* GetCurrentWeapon() {
		return _CurrentWeapon;
	}

	UFUNCTION(BlueprintCallable)
	FString GetAmmoText() {
		FString val = FString::FromInt(_CurrentWeapon->GetRemainingBullets()) + "/" + FString::FromInt(_CurrentWeapon->GetClipSize());
		return val;
	}

	UFUNCTION(BlueprintCallable)
		FString GetInteractPrompt();

	UFUNCTION(BlueprintCallable)
	float GetReloadPercentage() {
		if (!_CurrentWeapon->IsReloading()) return 0.0f;

		float timeRemaining = _CurrentWeapon->GetReloadTimeRemaining();

		return timeRemaining / _CurrentWeapon->GetReloadDuration();
	}

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* _pCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* _pFPSMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<AZombieWeapon> _StartingWeapon;

	AZombieWeapon* _CurrentWeapon;

	class AZombieWindow* _NearbyWindow = nullptr;

	UPROPERTY(VisibleAnywhere)
	float _maxHealth = 100.0f;

	float _currentHealth;

	bool _isDead = false;
};
