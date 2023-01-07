// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

#include "ZombieRoom.h"
#include "ZombieWeapon.h"
#include "AmmoTypes.h"

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

	void SetNearbyDoor(class AZombieDoor* Door) { _NearbyDoor = Door; }

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
	void StopFiring();

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Reload();

	UFUNCTION()
	void MouseWheelUp();

	UFUNCTION()
	void MouseWheelDown();

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
	class AZombieWeapon* GetCurrentWeapon() {
		return _CurrentWeapon;
	}

	UFUNCTION(BlueprintCallable)
	FString GetAmmoText() {
		if (_CurrentWeapon == nullptr) return "";

		return _CurrentWeapon->GetAmmoText();

		FString val = FString::FromInt(_CurrentWeapon->GetRemainingBullets()) + "/" + FString::FromInt(_CurrentWeapon->GetClipSize());
		return val;
	}

	UFUNCTION(BlueprintCallable)
		FString GetInteractPrompt();

	UFUNCTION(BlueprintCallable)
	float GetReloadPercentage() {
		if (_CurrentWeapon == nullptr) return 0.0f;

		if (!_CurrentWeapon->IsReloading()) return 0.0f;

		float timeRemaining = _CurrentWeapon->GetReloadTimeRemaining();

		return timeRemaining / _CurrentWeapon->GetReloadDuration();
	}

	void SetNearbyPickupWeapon(class AWeaponSpawnPoint* SpawnPoint) {
		_NearbyWeaponToPickup = SpawnPoint;
	}

	void EquipWeapon(class AZombieWeapon* Weapon);

	void AddRoom(class AZombieRoom* room);

	bool HasAmmo(AmmoType type) const;
	int ConsumeAmmo(AmmoType type, int amount);
	void GainAmmo(AmmoType type, int amount);
	int GetAmmo(AmmoType type) const {
		return _AmmoStore[(int)type];
	}

	class TArray<AZombieRoom*> GetRooms() const {
		return _PastRooms;
	}

protected:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* _pCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* _pFPSMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class AZombieWeapon> _StartingWeapon;

	UPROPERTY(VisibleAnywhere)
	float _maxHealth = 100.0f;

	class AZombieWeapon* _PrimaryWeapon;
	class AZombieWeapon* _SecondaryWeapon;

	class AZombieWeapon* _CurrentWeapon;

	class AWeaponSpawnPoint* _NearbyWeaponToPickup;

	class AZombieWindow* _NearbyWindow = nullptr;
	class AZombieDoor* _NearbyDoor = nullptr;

	class AZombieRoom* _CurrentRoom = nullptr;

	TArray<class AZombieRoom*> _PastRooms;

	TArray<uint32_t> _AmmoStore;



	float _currentHealth;

	bool _isDead = false;
};
