// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomVolume.h"
#include "ZombieDoor.h"
#include "ZombieWindow.h"
#include "Kismet/GameplayStatics.h"

void ARoomVolume::LoadStartAttributes()
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
}

void ARoomVolume::LoadEndAttributes()
{
	for (int i = 0; i < _DoorsInVolume.Num(); ++i) {
		AZombieDoor* door = _DoorsInVolume[i];

		door->SetRoom(door->GetClosestRoomCheck(GetActorLocation()), this);
	}
}

void ARoomVolume::ActivateRoom()
{
	for (int i = 0; i < _WindowsInVolume.Num(); ++i) {
		_WindowsInVolume[i]->ActivateWindow();
	}
}

template<typename T>
TArray<T*> ARoomVolume::CheckIntersect(TArray<AActor*> Input)
{
	TArray<T*> objects;
	FBoxSphereBounds volumeBounds = GetBounds();

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
