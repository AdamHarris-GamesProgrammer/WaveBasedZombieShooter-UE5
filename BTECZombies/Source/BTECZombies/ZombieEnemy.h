// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"


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

	void SetNearbyWindow(class AZombieWindow* Window) { _NearbyWindow = Window; }

	UFUNCTION(BlueprintCallable)
	void AttackAnimationEnded();

	int GetKillPoints() const {
		return _KillPoints;
	}

	void OnAIMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);

	UFUNCTION()
	void MoveToPlayer();

	UFUNCTION()
	void SeekPlayer();

	UFUNCTION()
	void StopSeekingPlayer();

	UFUNCTION()
	void OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void AttackPlayer();

protected:
	UPROPERTY()
		float _stoppingDistance = 100.0f;

	UPROPERTY(EditDefaultsOnly)
		int _KillPoints = 30;

	FTimerHandle _seekPlayerTimerHandle;

	UPROPERTY(VisibleAnywhere)
		float _maxHealth = 20.0f;
	float _currentHealth;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraSystem* _BloodVFX;

	class AZombiePlayerController* _pPlayerRef;

	UPROPERTY(EditAnywhere)
		class USphereComponent* _pPlayerAttackCollisionDetection;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* _pDamageCollisionDetection;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> _ZombieAttackSound;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> _ZombieSpawnSound;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> _ZombieDeathSound;

	class AZombieAIController* _pZombieAIController;

	bool IsDead = false;
	bool CanAttackPlayer;

	UPROPERTY(BlueprintReadWrite)
		bool CanDealDamage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* _pEnemyAttackMontage;

	class UAnimInstance* _pAnimInstance;

	class AZombieWindow* _NearbyWindow = nullptr;


};
