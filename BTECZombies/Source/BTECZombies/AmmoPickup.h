// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoTypes.h"
#include "AmmoPickup.generated.h"

UCLASS()
class BTECZOMBIES_API AAmmoPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPickupColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ammo Pickup")
	UStaticMeshComponent* _AmmoPickupMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo Pickup")
	int _AmountToPickup = 12;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo Pickup")
	TEnumAsByte<AmmoType> _AmmoTypeToPickup;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo Pickup")
	class USoundBase* _PickupSFX;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* _PickupCollider;
};
