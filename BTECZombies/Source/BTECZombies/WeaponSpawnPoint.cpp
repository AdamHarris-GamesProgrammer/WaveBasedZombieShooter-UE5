// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponSpawnPoint.h"
#include "Components/SphereComponent.h"
#include "ZombiePlayerController.h"

// Sets default values
AWeaponSpawnPoint::AWeaponSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	_SphereCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AWeaponSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	_SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponSpawnPoint::OnPlayerOverlapBegin);
	_SphereCollider->OnComponentEndOverlap.AddDynamic(this, &AWeaponSpawnPoint::OnPlayerOverlapEnd);


	if (_WeaponToSpawn != nullptr) {
		_Weapon = GetWorld()->SpawnActor<AZombieWeapon>(_WeaponToSpawn, GetActorLocation(), FRotator());
	}
}

// Called every frame
void AWeaponSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponSpawnPoint::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->SetNearbyPickupWeapon(this);
	}
}

void AWeaponSpawnPoint::OnPlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->SetNearbyPickupWeapon(nullptr);
	}
}
