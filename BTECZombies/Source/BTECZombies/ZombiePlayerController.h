// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "ZombieProjectile.h"

#include "ZombiePlayerController.generated.h"



UCLASS()
class BTECZOMBIES_API AZombiePlayerController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombiePlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Handles moving forward and backward
	UFUNCTION() //Adding UFUNCTION macro means that the engine is aware of these functions and will be included in serialization
	void MoveForward(float value);

	//Handles moving right and left
	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void Turn(float value);

	UFUNCTION()
	void LookUp(float value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void Fire();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* _pCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* _pFPSMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AZombieProjectile> ProjectileClass;

};
