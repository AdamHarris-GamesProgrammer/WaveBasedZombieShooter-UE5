// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieEnemy.h"

// Sets default values
AZombieEnemy::AZombieEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_pPlayerCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Collision Detection"));
	_pPlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Player Attack Collision Detection"));
	_pDamageCollisionDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	_pDamageCollisionDetection->SetupAttachment(GetMesh(), TEXT("RightHand"));

}

// Called when the game starts or when spawned
void AZombieEnemy::BeginPlay()
{
	Super::BeginPlay();
	

	_pZombieAIController = Cast<AZombieAIController>(GetController());

	if (_pZombieAIController) {
		_pZombieAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AZombieEnemy::OnAIMoveCompleted);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Failed to cast Zombie Controller!"));
	}

	if (_pPlayerCollisionDetection != nullptr) {
		_pPlayerCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemy::OnPlayerDetectedOverlapBegin);
		_pPlayerCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AZombieEnemy::OnPlayerDetectedOverlapEnd);

	}

	if (_pPlayerAttackCollisionDetection != nullptr) {
		_pPlayerAttackCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemy::OnPlayerAttackOverlapBegin);
		_pPlayerAttackCollisionDetection->OnComponentEndOverlap.AddDynamic(this, &AZombieEnemy::OnPlayerAttackOverlapEnd);

	}

	if (_pDamageCollisionDetection != nullptr) {
		_pDamageCollisionDetection->OnComponentBeginOverlap.AddDynamic(this, &AZombieEnemy::OnDealDamageOverlapBegin);
	}

	_pAnimInstance = GetMesh()->GetAnimInstance();
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
	if (CanAttackPlayer) {
		_pAnimInstance->Montage_Play(_pEnemyAttackMontage);
	}
}

void AZombieEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!PlayerDetected) {
		_pZombieAIController->RandomPatrol();
	}
	else if (PlayerDetected && CanAttackPlayer) {
		StopSeekingPlayer();

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Playing Anim"));
		_pAnimInstance->Montage_Play(_pEnemyAttackMontage);
	}
}

void AZombieEnemy::MoveToPlayer()
{
	if (_pPlayerRef == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player Ref is nullptr"));
		return;
	}
	_pZombieAIController->MoveToLocation(_pPlayerRef->GetActorLocation(), _stoppingDistance, true);
}

void AZombieEnemy::SeekPlayer()
{
	MoveToPlayer();
	//Params: Handle, class, callback, timer duration, in loop
	GetWorld()->GetTimerManager().SetTimer(_seekPlayerTimerHandle, this, &AZombieEnemy::SeekPlayer, 0.25f, true);
}

void AZombieEnemy::StopSeekingPlayer()
{
	GetWorld()->GetTimerManager().ClearTimer(_seekPlayerTimerHandle);
}

void AZombieEnemy::OnPlayerDetectedOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		_pPlayerRef = pc;
		PlayerDetected = true;
		SeekPlayer();
	}
}

void AZombieEnemy::OnPlayerDetectedOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		_pPlayerRef = pc;
		PlayerDetected = false;
		StopSeekingPlayer();
		_pZombieAIController->RandomPatrol();
	}
}

void AZombieEnemy::OnPlayerAttackOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		_pPlayerRef = pc;
		CanAttackPlayer = true;
	}
}

void AZombieEnemy::OnPlayerAttackOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		_pPlayerRef = pc;
		CanAttackPlayer = false;

		_pAnimInstance->Montage_Stop(0.0f, _pEnemyAttackMontage);
		SeekPlayer();
	}
}

void AZombieEnemy::OnDealDamageOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanDealDamage) {
		UE_LOG(LogTemp, Warning, TEXT("Attempting"));
	}

	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc && CanDealDamage) {
		_pPlayerRef = pc;
		UE_LOG(LogTemp, Warning, TEXT("Hitting Player"));
	}
}
