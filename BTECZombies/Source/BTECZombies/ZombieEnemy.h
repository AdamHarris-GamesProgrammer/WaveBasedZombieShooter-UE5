// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombiePlayerController.h"
#include "Components/BoxComponent.h"
#include "ZombieAIController.h"
#include "ZombieEnemy.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool PlayerDetected;
	bool CanAttackPlayer;

	UPROPERTY(BlueprintReadWrite)
	bool CanHealDamage;

	class AZombiePlayerCharacter* _pPlayerRef;

	UPROPERTY(EditAnywhere)
	USphereComponent* _pPlayerCollisionDetection;

	UPROPERTY(EditAnywhere)
	USphereComponent* _pPlayerAttackCollisionDetection;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _pDamageCollisionDetection;

	AZombieAIController* _pZombieAIController;

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

};
