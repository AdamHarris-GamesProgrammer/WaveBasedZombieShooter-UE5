// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieDoor.h"

#include "Components/BoxComponent.h"

#include "ZombiePlayerController.h"

// Sets default values
AZombieDoor::AZombieDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame"));
	RootComponent = _DoorFrame;

	_Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	_Door->SetupAttachment(RootComponent);

	_DoorTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger Volume"));
	_DoorTriggerVolume->SetupAttachment(_Door);

}

// Called when the game starts or when spawned
void AZombieDoor::BeginPlay()
{
	Super::BeginPlay();

	if (_DoorTriggerVolume != nullptr) {
		_DoorTriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AZombieDoor::OnTriggerVolumeOverlapBegin);
		_DoorTriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AZombieDoor::OnTriggerVolumePlayerOverlapEnd);
	}
}

void AZombieDoor::OnTriggerVolumeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->SetNearbyDoor(this);
	}
}

void AZombieDoor::OnTriggerVolumePlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AZombiePlayerController* pc = Cast<AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->SetNearbyDoor(nullptr);
	}
}

// Called every frame
void AZombieDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

