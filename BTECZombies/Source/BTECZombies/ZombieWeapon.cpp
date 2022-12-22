// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BTECZombiesGameModeBase.h"
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
	
	_AccuracyDebuff = 1.0f - _Accuracy;

	_gm = Cast<ABTECZombiesGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AZombieWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	for (int i = 0; i < _Bullets.Num(); ++i) {
		FHitResult hit;

		FVector p0 = GetPosition(_Bullets[i]);

		_Bullets[i].Time += DeltaTime;

		FVector p1 = GetPosition(_Bullets[i]);

		//Calculate the direction of the bullet
		FVector dir = (p0 - p1);
		dir.Normalize();

		if (_BulletTrailVFX != nullptr) {
			//Spawn our bullet trail vfx
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _BulletTrailVFX, p0, dir.Rotation());
		}
		
		//DrawDebugLine(GetWorld(), p0, p1, FColor::Red, false, 5.0f, 0U, 1.0f);

		if (_Bullets[i].CastSegment(World, hit, p0, p1)) {
			if (hit.GetActor() == nullptr) continue;
			
			_Bullets[i]._Stop = true;

			AZombieEnemy* enemy = Cast<AZombieEnemy>(hit.GetActor());
			if (enemy == nullptr) continue;

			FPointDamageEvent damageEvent(_WeaponDamage, hit, hit.ImpactNormal, nullptr);
			hit.GetActor()->TakeDamage(_WeaponDamage, damageEvent, _OwningController, this);
		}

		UpdateAttributes(_Bullets[i]);
	}

	//Removes all spent bullets
	_Bullets.RemoveAll([](Bullet bul) {
		return bul._Stop;
	});
}

void AZombieWeapon::StartReload()
{
	if (_isReloading) return;
	_isReloading = true;
	GetWorld()->GetTimerManager().SetTimer(_ReloadTimerHandle, this, &AZombieWeapon::FinishReload, _ReloadDuration, false);
	
	if (_StartReloadSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _StartReloadSFX, GetActorLocation(), 1.0f * _gm->GetSFXVoume());
	}
}

void AZombieWeapon::FinishReload()
{
	_isReloading = false;
	_CurrentBulletsInClip = _ClipSize;
	GetWorld()->GetTimerManager().ClearTimer(_ReloadTimerHandle);

	if (_EndReloadSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _EndReloadSFX, GetActorLocation(), 1.0f * _gm->GetSFXVoume());
	}
}

void AZombieWeapon::Fire()
{
	if (_isReloading) {
		EndFiring();
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	if (_CurrentBulletsInClip == 0) {
		if (_DryFireSFX != nullptr) {
			UGameplayStatics::PlaySoundAtLocation(World, _DryFireSFX, _MuzzleFlashLocation->GetComponentLocation(), 1.0f * _gm->GetSFXVoume());
		}
		return;
	}
	
	if (_FireSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(World, _FireSFX, _MuzzleFlashLocation->GetComponentLocation(), 1.0f * _gm->GetSFXVoume());
	}

	_CurrentBulletsInClip--;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _MuzzleVFX, _MuzzleFlashLocation->GetComponentLocation());

	FRotator Rotation = _Rotation;

	if (_ShootingPattern.Num() != 0) {
		_CurrentShootPatternIndex = (_CurrentShootPatternIndex + 1) % +_ShootingPattern.Num();
		FVector temp = Rotation.Vector() + _ShootingPattern[_CurrentShootPatternIndex] * _AccuracyDebuff;
		Rotation = temp.Rotation();
	}

	FVector dir = Rotation.Vector();
	for (int i = 0; i < _ProjectileCount; ++i) {
		Bullet bullet;
		bullet.InitialPosition = _MuzzleFlashLocation->GetComponentLocation();

		dir.Y += FMath::FRandRange(-_AccuracyDebuff, _AccuracyDebuff);
		dir.Z += FMath::FRandRange(-_AccuracyDebuff, _AccuracyDebuff);
		dir.Normalize();

		FVector velocity = dir * _BulletSpeed;
		bullet.InitialVelocity = velocity;
		_Bullets.Add(bullet);
	}
}

void AZombieWeapon::StartFiring()
{
	_IsFiring = true;

	if (_Automatic) {
		//Timer call here to repeat fire method every N seconds. Where N is the time between bullets
		GetWorld()->GetTimerManager().SetTimer(_AutoFireTimerHandle, this, &AZombieWeapon::Fire, _TimeBetweenShots, true, 0.0f);
	}
	else {
		Fire();
		EndFiring();
	}
}

void AZombieWeapon::EndFiring()
{
	_IsFiring = false;
	GetWorld()->GetTimerManager().ClearTimer(_AutoFireTimerHandle);
}

void AZombieWeapon::UpdateAttributes(Bullet& Bullet) {
	if (Bullet.Time > _BulletLifetime) {
		Bullet._Stop = true;
	}
}

FVector AZombieWeapon::GetPosition(Bullet& Bullet) {
	FVector gravity = FVector::DownVector * _BulletWeight;

	return Bullet.InitialPosition + (Bullet.InitialVelocity * Bullet.Time) + (0.5f * gravity * Bullet.Time * Bullet.Time);
}

