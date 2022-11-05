// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieProjectile.h"

// Sets default values
AZombieProjectile::AZombieProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent) {
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!_pCollisionComponent) {
		_pCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		_pCollisionComponent->InitSphereRadius(15.0f);
		_pCollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		RootComponent = _pCollisionComponent;
	}

	if (!_pProjectileMovementComponent) {
		_pProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		_pProjectileMovementComponent->SetUpdatedComponent(_pCollisionComponent);
		_pProjectileMovementComponent->InitialSpeed = 3000.0f;
		_pProjectileMovementComponent->MaxSpeed = 3000.0f;
		_pProjectileMovementComponent->bRotationFollowsVelocity = true;
		_pProjectileMovementComponent->bShouldBounce = true;
		_pProjectileMovementComponent->Bounciness = 0.3f;
		_pProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!_pProjectileMeshComponent) {
		_pProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Meshes/Sphere.Sphere'"));
		if (Mesh.Succeeded()) {
			_pProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}
	}

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Material/ProjectileMaterial.ProjectileMaterial'"));
	if (Material.Succeeded()) {
		_pProjectileMaterial = UMaterialInstanceDynamic::Create(Material.Object, _pProjectileMeshComponent);
	}
	_pProjectileMeshComponent->SetMaterial(0, _pProjectileMaterial);
	_pProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	_pProjectileMeshComponent->SetupAttachment(RootComponent);


	InitialLifeSpan = 3.0f;

	_pCollisionComponent->OnComponentHit.AddDynamic(this, &AZombieProjectile::OnHit);

}

// Called when the game starts or when spawned
void AZombieProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombieProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZombieProjectile::FireInDirection(const FVector& ShootDirection)
{
	_pProjectileMovementComponent->Velocity = ShootDirection * _pProjectileMovementComponent->InitialSpeed;
}

void AZombieProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics()) {
		OtherComponent->AddImpulseAtLocation(_pProjectileMovementComponent->Velocity * 10.0f, Hit.ImpactPoint);
	}

	Destroy();
}

