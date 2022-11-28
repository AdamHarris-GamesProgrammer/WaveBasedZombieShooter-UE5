// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ZombieWindow.h"
#include "BTECZombiesGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AZombieEnemy::AZombieEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_pPlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision Detection"));
	_pPlayerAttackCollisionDetection->SetupAttachment(RootComponent);

	_pDamageCollisionDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	_pDamageCollisionDetection->SetupAttachment(GetMesh(), TEXT("RightHand"));

	GetCharacterMovement()->MaxWalkSpeed = 100.0f;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

}

// Called when the game starts or when spawned
void AZombieEnemy::BeginPlay()
{
	Super::BeginPlay();


	_pZombieAIController = Cast<AZombieAIController>(GetController());

	if (_pZombieAIController) {
		_pZombieAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AZombieEnemy::OnAIMoveCompleted);
	}

	if (_pPlayerAttackCollisionDetection != nullptr) {
		_pPlayerAttackCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemy::OnPlayerAttackOverlapBegin);
		_pPlayerAttackCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AZombieEnemy::OnPlayerAttackOverlapEnd);
	}

	if (_pDamageCollisionDetection != nullptr) {
		_pDamageCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemy::OnDealDamageOverlapBegin);
	}

	_currentHealth = _maxHealth;
	_pAnimInstance = GetMesh()->GetAnimInstance();

	//_pZombieAIController->RandomPatrol();

	IsDead = false;
}

// Called every frame
void AZombieEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AZombieEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AZombieEnemy::AttackAnimationEnded()
{
	if (IsDead) return;
	AttackPlayer();
}

void AZombieEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (IsDead) return;
	if (CanAttackPlayer) {
		StopSeekingPlayer();

		AttackPlayer();
	}
}

void AZombieEnemy::MoveToPlayer()
{
	if (IsDead) return;
	if (_pPlayerRef == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Ref is nullptr"));
		return;
	}

	_pZombieAIController->MoveToLocation(_pPlayerRef->GetActorLocation(), _stoppingDistance, true);
}

void AZombieEnemy::SeekPlayer()
{
	if (IsDead) return;
	MoveToPlayer();
	//Params: Handle, class, callback, timer duration, in loop
	GetWorld()->GetTimerManager().SetTimer(_seekPlayerTimerHandle, this, &AZombieEnemy::SeekPlayer, 0.25f, true);
}

void AZombieEnemy::StopSeekingPlayer()
{
	if (IsDead) return;
	GetWorld()->GetTimerManager().ClearTimer(_seekPlayerTimerHandle);
}

void AZombieEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsDead) return;
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		_pPlayerRef = pc;
		CanAttackPlayer = true;
	}
}

void AZombieEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsDead) return;
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		_pPlayerRef = pc;
		CanAttackPlayer = false;
		CanDealDamage = false;

		if (_pAnimInstance) _pAnimInstance->Montage_Stop(0.0f, _pEnemyAttackMontage);
		SeekPlayer();
	}
}

void AZombieEnemy::OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsDead) return;
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc && CanDealDamage) {
		_pPlayerRef = pc;

		FPointDamageEvent e;

		_pPlayerRef->TakeDamage(10.0f, e, GetController(), this);
	}
}

float AZombieEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float dam = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (IsDead) return 0.0f;

	if (DamageEvent.IsOfType(1)) {
		const FPointDamageEvent* e = static_cast<const FPointDamageEvent*>(&DamageEvent);

		if (_BloodVFX != nullptr) {
			FRotator EmmiterRot = e->HitInfo.ImpactNormal.Rotation();
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _BloodVFX, e->HitInfo.Location, EmmiterRot);
		}

		float z = e->HitInfo.ImpactPoint.Z;

		float capsuleHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		float impactPoint = z - capsuleHeight;

		//Add a damage scale if we are above the hips
		float scale = 1.0f;
		if (impactPoint > capsuleHeight + (capsuleHeight / 2.0f)) {
			float diff = impactPoint - capsuleHeight;

			float percent = diff / capsuleHeight;
			scale += percent * 2.0f;
		}
		else if (impactPoint > capsuleHeight) {
			float diff = impactPoint - capsuleHeight;

			float percent = diff / capsuleHeight;
			scale += percent;
		}

		//UE_LOG(LogTemp, Warning, TEXT("Damage Scale: %f"), scale);

		dam *= scale;
	}

	_currentHealth -= dam;

	if (_currentHealth <= 0.0f) {
		_pPlayerRef = nullptr;
		//TODO: Trigger Point Gain

		if (_NearbyWindow) {
			_NearbyWindow->RemoveZombie(this);
		}

		IsDead = true;

		ABTECZombiesGameModeBase* gm = Cast<ABTECZombiesGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gm) {
			gm->EnemyKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Destroy();
	}

	return 0.0f;
}

void AZombieEnemy::AttackPlayer()
{
	if (!CanAttackPlayer || _pPlayerRef == nullptr) return;

	_pAnimInstance->Montage_Play(_pEnemyAttackMontage);
}
