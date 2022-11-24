// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieWeapon.h"
#include "WeaponSpawnPoint.generated.h"

UCLASS()
class BTECZOMBIES_API AWeaponSpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AZombieWeapon> _WeaponToSpawn;

	TSubclassOf<AZombieWeapon> GetWeaponToSpawn() {
		return _WeaponToSpawn;
	}

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* _SphereCollider;

	class UStaticMeshComponent* _WeaponMesh;

	AZombieWeapon* _Weapon;
};
