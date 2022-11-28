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
	
	_AccuracyDebuff = 1.0f - _Accuracy;
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

		FVector dir = (p0 - p1);
		dir.Normalize();

		

		DrawDebugLine(GetWorld(), p0, p1, FColor::Red, false, 5.0f, 0U, 1.0f);

		if (_BulletTrailVFX != nullptr) {
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _BulletTrailVFX, p0, dir.Rotation());
		}

		if (_Bullets[i].CastSegment(World, hit, p0, p1)) {
			if (hit.GetActor() == nullptr) continue;
			
			_Bullets[i]._Stop = true;

			AZombieEnemy* enemy = Cast<AZombieEnemy>(hit.GetActor());
			if (enemy == nullptr) continue;

			FPointDamageEvent e(_WeaponDamage, hit, hit.ImpactNormal, nullptr);

			hit.GetActor()->TakeDamage(_WeaponDamage, e, _OwningController, this);

			if (_BloodVFX != nullptr) {
				FRotator EmmiterRot = hit.ImpactNormal.Rotation();
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _BloodVFX, hit.Location, EmmiterRot);
			}
		}

		UpdateAttributes(_Bullets[i]);
	}

	_Bullets.RemoveAll([](Bullet bul) {
		return bul._Stop;
	});

	//UE_LOG(LogTemp, Warning, TEXT("Bullet Arr Size: %i"), _Bullets.Num());
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
			UGameplayStatics::PlaySoundAtLocation(World, _DryFireSFX, _Origin);
		}
		return;
	}
	
	if (_FireSFX != nullptr) {
		UGameplayStatics::PlaySoundAtLocation(World, _FireSFX, _Origin);
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
		bullet.InitialPosition = _Origin;

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

