// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ZombieRoom.generated.h"

UCLASS()
class BTECZOMBIES_API AZombieRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieRoom();

	void LoadStartAttributes();
	void LoadEndAttributes();

	void ActivateRoom();

	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	template<typename T>
	TArray<T*> CheckIntersect(TArray<AActor*> Input);

	bool ActivateOnBeginPlay() const {
		return _ActivateOnBeginPlay;
	}

	TArray<class AZombieWindow*> GetWindows() const {
		return _WindowsInVolume;
	}

protected:
	UPROPERTY(EditAnywhere)
	bool _ActivateOnBeginPlay = false;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* _pBox;

private:
	UFUNCTION()
	void OnPlayerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	TArray<class AZombieDoor*> _DoorsInVolume;

	UPROPERTY(EditAnywhere)
	TArray<class AZombieWindow*> _WindowsInVolume;
};
