// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieDoor.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieDoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	int GetCostToOpen() const {
		return _CostToOpen;
	}

	bool IsOpen() const {
		return _IsOpened;
	}

	void OpenDoor();

	class AZombieRoom* GetClosestRoom(const FVector Input);
	class AZombieRoom* GetOppositeRoom(const FVector Input);
	USceneComponent* GetClosestRoomCheck(const FVector Input);

	void SetRoom(USceneComponent* ClosestCheck, class AZombieRoom* InputRoom);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnTriggerVolumeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnTriggerVolumePlayerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* _DoorFrame;
	
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* _Door;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* _DoorTriggerVolume;


	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _RoomACheck;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* _RoomBCheck;

	class AZombieRoom* _RoomA;
	class AZombieRoom* _RoomB;

	UPROPERTY(EditAnywhere)
	int _CostToOpen = 500;


private:
	bool _IsOpened = false;
};
