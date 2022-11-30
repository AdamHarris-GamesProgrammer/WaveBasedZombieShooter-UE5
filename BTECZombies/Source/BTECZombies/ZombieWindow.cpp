// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieWindow.h"
#include "ZombieEnemy.h"

// Sets default values
AZombieWindow::AZombieWindow()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Window Mesh"));
	RootComponent = _Mesh;

	_BoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Board Mesh"));
	_BoardMesh->SetupAttachment(_Mesh);
	

	_OutsidePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Outside Point"));
	_OutsidePoint->SetupAttachment(_Mesh);

	_InsidePoint = CreateDefaultSubobject<USceneComponent>(TEXT("Inside Point"));
	_InsidePoint->SetupAttachment(_Mesh);

	_OutsideCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Zombie Collider"));
	_OutsideCollider->SetupAttachment(_OutsidePoint);

	_InsideCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Collider"));
	_InsideCollider->SetupAttachment(_InsidePoint);
}

// Called when the game starts or when spawned
void AZombieWindow::BeginPlay()
{
	Super::BeginPlay();
	
	_OutsideCollider->OnComponentBeginOverlap.AddDynamic(this, &AZombieWindow::OnOutsideColliderOverlapBegin);
	
	_InsideCollider->OnComponentBeginOverlap.AddDynamic(this, &AZombieWindow::OnInsideColliderOverlapBegin);
	_InsideCollider->OnComponentEndOverlap.AddDynamic(this, &AZombieWindow::OnInsideColliderOverlapEnd);

	_BoardMesh->SetVisibility(false);
	_BoardMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	_TeardownTimer = 0.0f;
}

// Called every frame
void AZombieWindow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_ZombiesInCollider.Num() > 0) {
		//UE_LOG(LogTemp, Warning, TEXT("Zombie Collider Size: %i"), _ZombiesInCollider.Num());
		_TeardownTimer += DeltaTime;
		if (_TeardownTimer > _TeardownTime) {
			TearDownBoard();
		}
	}
	else {
		_TeardownTimer = 0.0f;
	}

}

void AZombieWindow::BoardUpWindow()
{
	if (_isBlocked) return;

	_BoardMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	_BoardMesh->SetVisibility(true);
	_isBlocked = true;

}

void AZombieWindow::RemoveZombie(AZombieEnemy* Zombie)
{
	if (_ZombiesInCollider.Contains(Zombie)) {
		_ZombiesInCollider.Remove(Zombie);
	}
}

void AZombieWindow::OnOutsideColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombieEnemy* ze = Cast<AZombieEnemy>(OtherActor);

	if (ze) {
		if (!_isBlocked) {
			ze->SetActorLocation(_InsidePoint->GetComponentLocation());
		}
		else {
			ze->SetNearbyWindow(this);
			_ZombiesInCollider.Add(ze);
		}

	}
}

void AZombieWindow::OnOutsideColliderOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZombieEnemy* ze = Cast<AZombieEnemy>(OtherActor);
	if (ze) {
		if (_ZombiesInCollider.Contains(ze)) {
			ze->SetNearbyWindow(nullptr);
			_ZombiesInCollider.Remove(ze);
		}
	}

}

void AZombieWindow::OnInsideColliderOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->SetNearbyWindow(this);
	}
}

void AZombieWindow::OnInsideColliderOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->SetNearbyWindow(nullptr);
	}
}

void AZombieWindow::TearDownBoard()
{
	_isBlocked = false;
	_BoardMesh->SetVisibility(false);
	_BoardMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	_TeardownTimer = 0.0f;
	
	for (AZombieEnemy* ze : _ZombiesInCollider) {
		if (ze == nullptr) continue;

		ze->SetActorLocation(_InsidePoint->GetComponentLocation());
	}
	_ZombiesInCollider.Empty();
}

