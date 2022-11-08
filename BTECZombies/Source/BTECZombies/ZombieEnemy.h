// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ZombiePlayerController.h"
#include "Components/BoxComponent.h"
#include "ZombieAIController.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

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
	bool CanDealDamage;

	UPROPERTY(EditAnywhere)
	UAnimMontage* _pEnemyAttackMontage;

	UAnimInstance* _pAnimInstance;

	UFUNCTION(BlueprintCallable)
	void AttackAnimationEnded();

	AZombiePlayerController* _pPlayerRef;

	UPROPERTY(EditAnywhere)
	USphereComponent* _pPlayerCollisionDetection;

	UPROPERTY(EditAnywhere)
	USphereComponent* _pPlayerAttackCollisionDetection;

	UPROPERTY(EditAnywhere)
	UBoxComponent* _pDamageCollisionDetection;

	AZombieAIController* _pZombieAIController;

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

	UPROPERTY()
	float _stoppingDistance = 100.0f;

	FTimerHandle _seekPlayerTimerHandle;

	UFUNCTION()
	void MoveToPlayer();

	UFUNCTION()
	void SeekPlayer();

	UFUNCTION()
	void StopSeekingPlayer();

	UFUNCTION()
	void OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	void AttackPlayer();
};
