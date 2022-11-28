// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ZombieWeapon.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieWeapon();

	void Init(AController* OwningController);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StartReload();
	void FinishReload();

	bool _isReloading = false;



	FTimerHandle _ReloadTimerHandle;

	UPROPERTY(EditDefaultsOnly)
	float _Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float _Range = 1500.0f;

	UPROPERTY(EditDefaultsOnly)
	int _ClipSize = 14;

	UPROPERTY(EditDefaultsOnly)
	float _ReloadDuration = 2.5f;

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
	FString GetAmmoText() {
		FString val = FString::FromInt(_CurrentBulletsInClip) + "/" + FString::FromInt(_ClipSize);
		return val;
	}

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
	void EndFiring();

	AController* _OwningController;

	UPROPERTY(EditDefaultsOnly)
	float _WeaponDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _MuzzleVFX;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _BloodVFX;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _WallImpactVFX;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _BulletTrailVFX;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* _Mesh;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* _FireSFX;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* _DryFireSFX;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* _StartReloadSFX;

	UPROPERTY(EditDefaultsOnly, Category = SFX)
	USoundBase* _EndReloadSFX;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _MuzzleFlashLocation;

	int _CurrentBulletsInClip;

	UPROPERTY(EditDefaultsOnly)
	float _Accuracy = 0.95f;

	float _AccuracyDebuff;

	UPROPERTY(EditDefaultsOnly)
	float _RecoilStrength = 1.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<FVector> _ShootingPattern;

	int _CurrentShootPatternIndex = 0;

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

	bool _IsFiring = false;

	UPROPERTY(EditDefaultsOnly)
	float _TimeBetweenShots = 0.3f;

	FTimerHandle _AutoFireTimerHandle;

	void SetOriginRotation(FVector Origin, FRotator Rotation) {
		_Origin = Origin;
		_Rotation = Rotation;
	}

	FVector _Origin;
	FRotator _Rotation;

	struct Bullet {
		FVector InitialPosition = FVector();
		FVector InitialVelocity = FVector();

		float Time = 0.00f;

		bool _Stop = false;

		bool CastSegment(UWorld* World, FHitResult& Hit, FVector Start, FVector End) {
			if (_Stop) return false;

			return World->LineTraceSingleByChannel(Hit, Start, End,ECC_Visibility);
		}
	};

	void UpdateAttributes(Bullet& Bullet);

	FVector GetPosition(Bullet& Bullet);

	TArray<Bullet> _Bullets;
};
