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
	_pDamageCollisionDetection->SetupAttachment(GetMesh(), TEXT("hand_r"));

}

// Called when the game starts or when spawned
void AZombieEnemy::BeginPlay()
{
	Super::BeginPlay();
	

	_pZombieAIController = Cast<AZombieAIController>(GetController());

	_pZombieAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AZombieEnemy::OnAIMoveCompleted);
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

void AZombieEnemy::OnAIMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	_pZombieAIController->RandomPatrol();
}

