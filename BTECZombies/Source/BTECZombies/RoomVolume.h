// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LocationVolume.h"
#include "RoomVolume.generated.h"

/**
 * 
 */
UCLASS()
class BTECZOMBIES_API ARoomVolume : public ALocationVolume
{
	GENERATED_BODY()
	

public:
	void LoadStartAttributes();
	void LoadEndAttributes();

	void ActivateRoom();

	virtual void BeginPlay() override;

	template<typename T>
	TArray<T*> CheckIntersect(TArray<AActor*> Input);

	bool ActivateOnBeginPlay() const {
		return _ActivateOnBeginPlay;
	}

protected:
	UPROPERTY(EditAnywhere)
	bool _ActivateOnBeginPlay = false;

	class UBoxComponent* _pBox;



private:
	TArray<class AZombieDoor*> _DoorsInVolume;
	TArray <class AZombieWindow* > _WindowsInVolume;

};


