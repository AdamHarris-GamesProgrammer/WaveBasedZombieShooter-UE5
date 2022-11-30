// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieDoor.h"

#include "Components/BoxComponent.h"
#include "RoomVolume.h"

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

	_RoomACheck = CreateDefaultSubobject<USceneComponent>(TEXT("Room A Check"));
	_RoomACheck->SetupAttachment(_Door);

	_RoomBCheck = CreateDefaultSubobject<UBoxComponent>(TEXT("Room B Check"));
	_RoomBCheck->SetupAttachment(_Door);

}

inline void AZombieDoor::OpenDoor() {
	UE_LOG(LogTemp, Warning, TEXT("Opening Door"));

	_IsOpened = true;

	_Door->SetCanEverAffectNavigation(false);

	FRotator rot = _Door->GetRelativeRotation();

	rot.Yaw += 90.0f;

	_Door->SetRelativeRotation(rot);

	if (_RoomA) _RoomA->ActivateRoom();
	if (_RoomB) _RoomB->ActivateRoom();
}

ARoomVolume* AZombieDoor::GetClosestRoom(const FVector Input)
{
	if (_RoomA == nullptr && _RoomB == nullptr) return nullptr;
	if (_RoomA == nullptr) return _RoomB;
	if (_RoomB == nullptr) return _RoomA;

	float distToA = FVector::Dist(Input, _RoomACheck->GetComponentLocation());
	float distToB = FVector::Dist(Input, _RoomACheck->GetComponentLocation());

	return distToA < distToB ? _RoomA : _RoomB;
}

ARoomVolume* AZombieDoor::GetOppositeRoom(const FVector Input)
{
	if (_RoomA == nullptr && _RoomB == nullptr) return nullptr;
	if (_RoomA == nullptr) return _RoomB;
	if (_RoomB == nullptr) return _RoomA;

	float distToA = FVector::Dist(Input, _RoomACheck->GetComponentLocation());
	float distToB = FVector::Dist(Input, _RoomACheck->GetComponentLocation());

	return distToA < distToB ?  _RoomB : _RoomA;
}

USceneComponent* AZombieDoor::GetClosestRoomCheck(const FVector Input)
{
	float distToA = FVector::Dist(Input, _RoomACheck->GetComponentLocation());
	float distToB = FVector::Dist(Input, _RoomACheck->GetComponentLocation());

	return distToA < distToB ? _RoomACheck : _RoomBCheck;
}

void AZombieDoor::SetRoom(USceneComponent* ClosestCheck, class ARoomVolume* InputRoom)
{
	if (ClosestCheck == _RoomACheck) {
		_RoomA = InputRoom;
	}
	else if (ClosestCheck == _RoomBCheck) {
		_RoomB = InputRoom;
	}
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

