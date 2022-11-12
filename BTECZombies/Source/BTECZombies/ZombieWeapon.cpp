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

void AZombieWeapon::PullTrigger(FVector Origin, FRotator Rotation)
{
	UWorld* World = GetWorld();
	if (!World) return;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _MuzzleVFX, _MuzzleFlashLocation->GetComponentLocation());

	FHitResult hit;
	if (World->LineTraceSingleByChannel(hit, Origin, Origin + Rotation.Vector() * _Range, ECC_Pawn)) {
		if (hit.GetActor() == nullptr) return;

		AZombieEnemy* enemy = Cast<AZombieEnemy>(hit.GetActor());
		
		FRotator EmmiterRot = hit.ImpactNormal.Rotation();

		if (enemy == nullptr) {
			return;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Hit Name: %s"), *hit.GetActor()->GetName());

		FPointDamageEvent e(10.0f, hit, hit.ImpactNormal, nullptr);

		hit.GetActor()->TakeDamage(5.0f, e, _OwningController, this);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, _BloodVFX, hit.Location, EmmiterRot);
	}
}
