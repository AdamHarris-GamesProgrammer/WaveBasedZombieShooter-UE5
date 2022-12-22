// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieRoom.h"
#include "ZombieDoor.h"
#include "ZombieWindow.h"
#include "Kismet/GameplayStatics.h"
#include "ZombiePlayerController.h"
#include "ZombieDoor.h"
#include "ZombieWindow.h"
#include "Components/BoxComponent.h"

// Sets default values
AZombieRoom::AZombieRoom()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	_pBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AZombieRoom::BeginPlay()
{
	Super::BeginPlay();

	_pBox->OnComponentBeginOverlap.AddDynamic(this, &AZombieRoom::OnPlayerOverlapBegin);

	LoadEndAttributes();

	if (_ActivateOnBeginPlay) {
		AZombiePlayerController* pc = Cast <AZombiePlayerController>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (pc) {
			pc->AddRoom(this);
		}
	}

}

// Called every frame
void AZombieRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieRoom::LoadStartAttributes()
{
	UWorld* World = GetWorld();

	TArray<AActor*> doors;
	UGameplayStatics::GetAllActorsOfClass(World, AZombieDoor::StaticClass(), doors);

	_DoorsInVolume = CheckIntersect<AZombieDoor>(doors);
	UE_LOG(LogTemp, Warning, TEXT("Doors in Room: %i"), _DoorsInVolume.Num());

	TArray<AActor*> windows;
	UGameplayStatics::GetAllActorsOfClass(World, AZombieWindow::StaticClass(), windows);

	_WindowsInVolume = CheckIntersect<AZombieWindow>(windows);
	UE_LOG(LogTemp, Warning, TEXT("Windows in Room: %i"), _WindowsInVolume.Num());

	bGenerateOverlapEventsDuringLevelStreaming = true;
}

void AZombieRoom::LoadEndAttributes()
{
	for (int i = 0; i < _DoorsInVolume.Num(); ++i) {
		AZombieDoor* door = _DoorsInVolume[i];

		door->SetRoom(door->GetClosestRoomCheck(GetActorLocation()), this);
	}
}

void AZombieRoom::ActivateRoom()
{
	for (int i = 0; i < _WindowsInVolume.Num(); ++i) {
		_WindowsInVolume[i]->ActivateWindow();
	}
}

void AZombieRoom::OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AZombiePlayerController* pc = Cast <AZombiePlayerController>(OtherActor);
	if (pc) {
		pc->AddRoom(this);
	}
}

template<typename T>
TArray<T*> AZombieRoom::CheckIntersect(TArray<AActor*> Input)
{
	TArray<T*> objects;

	FBoxSphereBounds volumeBounds = _pBox->GetLocalBounds();

	for (int i = 0; i < Input.Num(); ++i) {
		FVector objLocation = Input[i]->GetActorLocation();

		FBox box;
		box.Min = objLocation;
		box.Max = objLocation;

		if (volumeBounds.GetBox().Intersect(box)) {
			T* o = Cast<T>(Input[i]);
			if (o) {
				objects.Add(o);
			}
		}
	}

	return objects;
}
