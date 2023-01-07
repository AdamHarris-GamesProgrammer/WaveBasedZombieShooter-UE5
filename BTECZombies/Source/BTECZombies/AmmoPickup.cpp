// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "Components/SphereComponent.h"
#include "ZombiePlayerController.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
AAmmoPickup::AAmmoPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_AmmoPickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Box Mesh"));
	RootComponent = _AmmoPickupMesh;

	_PickupCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Pickup Collider"));
	_PickupCollider->SetupAttachment(_AmmoPickupMesh);
}

// Called when the game starts or when spawned
void AAmmoPickup::BeginPlay()
{
	Super::BeginPlay();
	
	_PickupCollider->OnComponentBeginOverlap.AddDynamic(this, &AAmmoPickup::OnPickupColliderOverlapBegin);
}

// Called every frame
void AAmmoPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoPickup::OnPickupColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->GainAmmo(_AmmoTypeToPickup, _AmountToPickup);

		if (_PickupSFX != nullptr) {
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), _PickupSFX, GetActorLocation());
		}

		GetWorld()->DestroyActor(this);
	}
}

