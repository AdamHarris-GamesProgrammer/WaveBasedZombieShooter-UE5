// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawnPoint.h"
#include "ZombieWindow.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieWindow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AZombieWindow();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BoardUpWindow();

	int GetBlockCost() const {
		return _BlockCost;
	}

	bool IsBlocked() const {
		return _isBlocked;
	}

	void ActivateWindow();

	void RemoveZombie(class AZombieEnemy* Zombie);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOutsideColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOutsideColliderOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnInsideColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnInsideColliderOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
		void TearDownBoard();

protected:
	UPROPERTY()
	TArray<class AZombieEnemy*> _ZombiesInCollider;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* _Mesh;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* _BoardMesh;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* _OutsidePoint;

	UPROPERTY(EditDefaultsOnly)
		class USceneComponent* _InsidePoint;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* _OutsideCollider;

	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* _InsideCollider;

	UPROPERTY(EditDefaultsOnly)
		float _TeardownTime = 2.5f;

	UPROPERTY(EditAnywhere)
		int _BlockCost = 500;

	UPROPERTY(EditAnywhere)
	TArray<AZombieSpawnPoint*> _ConnectedSpawnPoints;

private:
	bool _isBlocked = false;

	bool _IsActivated = false;

	float _TeardownTimer = 0.0f;
};
