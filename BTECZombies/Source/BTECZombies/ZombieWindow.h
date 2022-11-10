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


	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* _Mesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _OutsidePoint;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _InsidePoint;
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* _OutsideCollider;


	bool _isBlocked = false;

	UFUNCTION()
	void OnOutsideColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
