// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "ZombieWindow.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieWindow : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AZombieWindow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BoardUpWindow();

	UPROPERTY(EditDefaultsOnly)
	float _TeardownTime = 2.5f;

	float _TeardownTimer = 0.0f;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* _Mesh;

	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* _BoardMesh;

	UPROPERTY(EditDefaultsOnly)
		USceneComponent* _OutsidePoint;
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* _InsidePoint;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* _OutsideCollider;

	UPROPERTY(EditDefaultsOnly)
		UBoxComponent* _InsideCollider;

	UPROPERTY()
	TArray<class AZombieEnemy*> _ZombiesInCollider;

	bool _isBlocked = false;

	void RemoveZombie(class AZombieEnemy* Zombie);

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
};
