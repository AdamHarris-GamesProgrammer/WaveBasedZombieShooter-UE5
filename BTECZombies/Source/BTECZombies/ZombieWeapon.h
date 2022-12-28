// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoTypes.h"

#include "ZombieWeapon.generated.h"

struct Bullet {
	FVector InitialPosition = FVector();
	FVector InitialVelocity = FVector();

	float Time = 0.00f;

	bool _Stop = false;

	bool CastSegment(UWorld* World, FHitResult& Hit, FVector Start, FVector End) {
		if (_Stop) return false;

		return World->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility);
	}

	void UpdateAttributes(float lifetime) {
		if (Time > lifetime) {
			_Stop = true;
		}
	}
};

UCLASS()
class BTECZOMBIES_API AZombieWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AZombieWeapon();

	void Init(class AController* OwningController, class AZombiePlayerController* WeaponOwner);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartReload();
	void FinishReload();

	UFUNCTION(BlueprintCallable)
		float GetReloadTimeRemaining() const {
		if (!_isReloading) return 0.0f;

		return GetWorld()->GetTimerManager().GetTimerRemaining(_ReloadTimerHandle);
	}

	int GetClipSize() const {
		return _ClipSize;
	}

	int GetRemainingBullets() const {
		return _CurrentBulletsInClip;
	}

	UFUNCTION(BlueprintCallable)
	FString GetAmmoText();

	UFUNCTION(BlueprintCallable)
		float GetReloadPercentage() {
		if (!_isReloading) return 0.0f;

		float timeRemaining = GetReloadTimeRemaining();

		return timeRemaining / _ReloadDuration;
	}

	UFUNCTION(BlueprintCallable)
		bool IsReloading() {
		return _isReloading;
	}

	bool IsFiring() const {
		return _IsFiring;
	}

	UFUNCTION(BlueprintCallable)
		float GetReloadDuration() {
		return _ReloadDuration;
	}

	void Hide(bool val) {
		SetHidden(val);
		SetActorHiddenInGame(val);
		_Mesh->SetOwnerNoSee(val);
	}

	void StartFiring();
	void Fire();
	void CreateBullet(FVector dir);
	void EndFiring();

	FVector GetPosition(Bullet& Bullet);

private:
	void UpdateBullets(float DeltaTime);
	void Play3DSound(class USoundBase* sfx, FVector location, float volumeMultiplier);
	void Play3DEmmiter(class UNiagaraSystem* vfx, FVector location, FRotator rotation = FRotator::ZeroRotator);
protected:
	bool _isReloading = false;

	FTimerHandle _ReloadTimerHandle;

	class AController* _OwningController;
	class AZombiePlayerController* _WeaponOwner;

	int _CurrentShootPatternIndex = 0;

	int _CurrentBulletsInClip;

	float _AccuracyDebuff;

	FTimerHandle _AutoFireTimerHandle;
	bool _IsFiring = false;

	TArray<Bullet> _Bullets;

	UPROPERTY(EditDefaultsOnly)
	float _WeaponDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* _MuzzleVFX;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* _WallImpactVFX;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* _BulletTrailVFX;

	UPROPERTY(EditDefaultsOnly)
	class USkeletalMeshComponent* _Mesh;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	class USoundBase* _FireSFX;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	class USoundBase* _DryFireSFX;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	class USoundBase* _StartReloadSFX;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	class USoundBase* _EndReloadSFX;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _MuzzleFlashLocation;

	UPROPERTY(EditDefaultsOnly)
	float _Accuracy = 0.95f;

	UPROPERTY(EditDefaultsOnly)
	float _RecoilStrength = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> _ShootingPattern;

	UPROPERTY(EditDefaultsOnly)
	float _BulletWeight = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float _BulletSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly)
	float _BulletLifetime = 5.0f;

	UPROPERTY(EditDefaultsOnly)
	int _ProjectileCount = 1;

	UPROPERTY(EditDefaultsOnly)
	bool _Automatic = false;

	UPROPERTY(EditDefaultsOnly)
	float _TimeBetweenShots = 0.3f;

	UPROPERTY(EditDefaultsOnly)
	float _Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float _Range = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	int _ClipSize = 14;

	UPROPERTY(EditDefaultsOnly)
	float _ReloadDuration = 2.5f;

	class ABTECZombiesGameModeBase* _gm;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<AmmoType> _AmmoType;
};
