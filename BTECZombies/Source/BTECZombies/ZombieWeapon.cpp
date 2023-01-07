// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombieWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BTECZombiesGameModeBase.h"
#include "ZombieEnemy.h"
#include "ZombiePlayerController.h"

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

void AZombieWeapon::Init(AController* OwningController, AZombiePlayerController* WeaponOwner)
{
	_OwningController = OwningController;
	_WeaponOwner = WeaponOwner;
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
	UpdateBullets(DeltaTime);
}

void AZombieWeapon::StartReload()
{
	if (_isReloading || _CurrentBulletsInClip == _ClipSize) return;

	//Get weapon owner and check we have the required ammo type
	if (_WeaponOwner && !_WeaponOwner->HasAmmo(_AmmoType)) {
		//TODO: Turn ammo ui red here
		return;
	}

	_isReloading = true;
	GetWorld()->GetTimerManager().SetTimer(_ReloadTimerHandle, this, &AZombieWeapon::FinishReload, _ReloadDuration, false);
	Play3DSound(_StartReloadSFX, GetActorLocation(), _gm->GetSFXVoume());
}

void AZombieWeapon::FinishReload()
{
	_isReloading = false;

	//consume ammo from the weapon owner
	if (_WeaponOwner) {
		//clip size 7 bullets in clip 3. 7 - 3 = 4. Therefore 4 bullets are required
		int neededAmmo = _ClipSize - _CurrentBulletsInClip;
		_CurrentBulletsInClip += _WeaponOwner->ConsumeAmmo(_AmmoType, neededAmmo);
	}

	GetWorld()->GetTimerManager().ClearTimer(_ReloadTimerHandle);
	Play3DSound(_EndReloadSFX, GetActorLocation(), _gm->GetSFXVoume());
}

inline FString AZombieWeapon::GetAmmoText() {
	int totalBullets = 0;

	if (_WeaponOwner != nullptr) {
		totalBullets = _WeaponOwner->GetAmmo(_AmmoType);
	}
	FString val = FString::FromInt(_CurrentBulletsInClip) + "/" + FString::FromInt(totalBullets);
	return val;
}

void AZombieWeapon::Fire()
{
	if (_isReloading) {
		EndFiring();
		return;
	}

	//Play Dry Fire SFX if needed
	if (_CurrentBulletsInClip == 0) {
		Play3DSound(_DryFireSFX, _MuzzleFlashLocation->GetComponentLocation(), _gm->GetSFXVoume());
		return;
	}
	_CurrentBulletsInClip--;

	//Play fire sfx/muzzle flash vfx
	Play3DSound(_FireSFX, _MuzzleFlashLocation->GetComponentLocation(), _gm->GetSFXVoume());
	Play3DEmmiter(_MuzzleVFX, _MuzzleFlashLocation->GetComponentLocation());

	FRotator rotation = _MuzzleFlashLocation->GetForwardVector().Rotation();

	//Progress through the shooting pattern array and adjust firing direction
	if (_ShootingPattern.Num() != 0) {
		_CurrentShootPatternIndex = (_CurrentShootPatternIndex + 1) % +_ShootingPattern.Num();
		FVector temp = rotation.Vector() + _ShootingPattern[_CurrentShootPatternIndex] * _AccuracyDebuff;
		rotation = temp.Rotation();
	}

	//Cycle through each projectile the gun fires and create a bullet
	for (int i = 0; i < _ProjectileCount; ++i) {
		CreateBullet(rotation.Vector());
	}
}

void AZombieWeapon::CreateBullet(FVector dir)
{
	Bullet bullet;
	bullet.InitialPosition = _MuzzleFlashLocation->GetComponentLocation();

	dir.Y += FMath::FRandRange(-_AccuracyDebuff, _AccuracyDebuff);
	dir.Z += FMath::FRandRange(-_AccuracyDebuff, _AccuracyDebuff);
	dir.Normalize();

	FVector velocity = dir * _BulletSpeed;
	bullet.InitialVelocity = velocity;
	_Bullets.Add(bullet);
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

FVector AZombieWeapon::GetPosition(Bullet& Bullet) {
	FVector gravity = FVector::DownVector * _BulletWeight;

	return Bullet.InitialPosition + (Bullet.InitialVelocity * Bullet.Time) + (0.5f * gravity * Bullet.Time * Bullet.Time);
}

void AZombieWeapon::UpdateBullets(float DeltaTime)
{
	if (_Bullets.Num() == 0) return;

	UWorld* World = GetWorld();
	Bullet& bullet = _Bullets[0];
	for (int i = 0; i < _Bullets.Num(); ++i) {

		FHitResult hit;

		FVector p0 = GetPosition(bullet);
		bullet.Time += DeltaTime;
		FVector p1 = GetPosition(bullet);

		//Calculate the direction of the bullet
		FVector dir = (p0 - p1);
		dir.Normalize();

		Play3DEmmiter(_BulletTrailVFX, p0, dir.Rotation());

		//DrawDebugLine(GetWorld(), p0, p1, FColor::Red, false, 5.0f, 0U, 1.0f);

		if (bullet.CastSegment(World, hit, p0, p1)) {
			if (hit.GetActor() == nullptr) continue;

			bullet._Stop = true;

			AZombieEnemy* enemy = Cast<AZombieEnemy>(hit.GetActor());
			if (enemy == nullptr) continue;

			FPointDamageEvent damageEvent(_WeaponDamage, hit, hit.ImpactNormal, nullptr);
			hit.GetActor()->TakeDamage(_WeaponDamage, damageEvent, _OwningController, this);
		}

		bullet.UpdateAttributes(_BulletLifetime);
	}

	//Removes all spent bullets
	_Bullets.RemoveAll([](Bullet bul) {
		return bul._Stop;
		});
}

void AZombieWeapon::Play3DSound(USoundBase* sfx, FVector location, float volumeMultiplier)
{
	if (sfx == nullptr) return;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), sfx, location, 1.0f * volumeMultiplier);
}

void AZombieWeapon::Play3DEmmiter(UNiagaraSystem* vfx, FVector location, FRotator rotation)
{
	if (vfx == nullptr) return;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), vfx, location, rotation);
}

