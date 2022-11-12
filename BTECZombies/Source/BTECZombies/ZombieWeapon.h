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

	void PullTrigger(FVector Origin, FRotator Rotation);

	UPROPERTY(EditAnywhere)
	float _Damage = 10.0f;

	UPROPERTY(EditAnywhere)
	float _Range = 1500.0f;

	UPROPERTY(EditAnywhere)
	int _ClipSize = 14;

	AController* _OwningController;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _MuzzleVFX;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _BloodVFX;

	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* _WallImpactVFX;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* _Mesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _MuzzleFlashLocation;

	int _CurrentBulletsInClip;

	//TODO: Add in SFX, VFX

};
