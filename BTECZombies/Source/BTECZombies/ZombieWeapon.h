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

	void PullTrigger(FVector Origin, FRotator Rotation);

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

	UFUNCTION(BlueprintCallable)
	float GetReloadDuration() {
		return _ReloadDuration;
	}

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

};
