// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieWindow.h"
#include "ZombieEnemy.h"

// Sets default values
AZombieWindow::AZombieWindow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Block"));


	_OutsidePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Outside Point"));
	_OutsidePoint->SetupAttachment(_Mesh);

	_InsidePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Inside Point"));
	_InsidePoint->SetupAttachment(_Mesh);

	_OutsideCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	_OutsideCollider->SetupAttachment(_OutsidePoint);
}

// Called when the game starts or when spawned
void AZombieWindow::BeginPlay()
{
	Super::BeginPlay();
	
	_OutsideCollider->OnComponentBeginOverlap.AddDynamic(this, &AZombieWindow::OnOutsideColliderOverlapBegin);
}

// Called every frame
void AZombieWindow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieWindow::OnOutsideColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombieEnemy* ze = Cast<AZombieEnemy>(OtherActor);
	if (ze) {
		ze->SetActorLocation(_InsidePoint->GetComponentLocation());
	}
}

