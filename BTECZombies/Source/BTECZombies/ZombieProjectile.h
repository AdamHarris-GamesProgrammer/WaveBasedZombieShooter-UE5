// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ZombieProjectile.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* _pCollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement);
	UProjectileMovementComponent* _pProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UStaticMeshComponent* _pProjectileMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UMaterialInstanceDynamic* _pProjectileMaterial;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
