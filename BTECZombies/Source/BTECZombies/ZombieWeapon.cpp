// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ZombieWeapon.h"
#include "ZombieEnemy.h"

// Sets default values
AZombieWeapon::AZombieWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	RootComponent = _Mesh;

	_MuzzleFlashLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Flash Location"));
	_MuzzleFlashLocation->SetupAttachment(_Mesh);
}

void AZombieWeapon::Init(AController* OwningController)
{
	_OwningController = OwningController;
	_CurrentBulletsInClip = _ClipSize;
}

// Called when the game starts or when spawned
void AZombieWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieWeapon::StartReload()
{
	if (_isReloading) return;
	_isReloading = true;
	GetWorld()->GetTimerManager().SetTimer(_ReloadTimerHandle, this, &AZombieWeapon::FinishReload, _ReloadDuration, false);
	
	if (_StartReloadSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _StartReloadSFX, GetActorLocation());
	}
}

void AZombieWeapon::FinishReload()
{
	_isReloading = false;
	_CurrentBulletsInClip = _ClipSize;
	GetWorld()->GetTimerManager().ClearTimer(_ReloadTimerHandle);

	if (_EndReloadSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _EndReloadSFX, GetActorLocation());
	}
}

void AZombieWeapon::PullTrigger(FVector Origin, FRotator Rotation)
{
	if (_isReloading) return;

	UWorld* World = GetWorld();
	if (!World) return;

	if (_CurrentBulletsInClip == 0) {
		if (_DryFireSFX != nullptr) {
			UGameplayStatics::PlaySoundAtLocation(World, _DryFireSFX, Origin);
		}
		return;
	}


	if (_FireSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(World, _FireSFX, Origin);
	}
	_CurrentBulletsInClip--;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _MuzzleVFX, _MuzzleFlashLocation->GetComponentLocation());

	FHitResult hit;
	if (World->LineTraceSingleByChannel(hit, Origin, Origin + Rotation.Vector() * _Range, ECC_Visibility)) {
		if (hit.GetActor() == nullptr) return;

		AZombieEnemy* enemy = Cast<AZombieEnemy>(hit.GetActor());

		FRotator EmmiterRot = hit.ImpactNormal.Rotation();

		if (enemy == nullptr) {
			return;
		}

		FPointDamageEvent e(_WeaponDamage, hit, hit.ImpactNormal, nullptr);

		hit.GetActor()->TakeDamage(_WeaponDamage, e, _OwningController, this);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _BloodVFX, hit.Location, EmmiterRot);
	}
}

