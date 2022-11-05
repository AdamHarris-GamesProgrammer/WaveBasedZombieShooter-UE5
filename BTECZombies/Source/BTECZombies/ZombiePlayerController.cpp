// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiePlayerController.h"
#include "Camera/CameraComponent.h"

// Sets default values
AZombiePlayerController::AZombiePlayerController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_pCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(_pCameraComponent != nullptr);

	//Attaches our camera to the capsule component.
	//Uses CastChecked. CastChecked will assert if the cast is unsuccessful. Cannot return nullptr
	_pCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	_pCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	_pCameraComponent->bUsePawnControlRotation = true;

	_pFPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS Mesh"));
	check(_pFPSMesh != nullptr);
	
	//Only visible to the player controller that has possessed this character
	_pFPSMesh->SetOnlyOwnerSee(true);
	
	//Attach the mesh to our camera component
	_pFPSMesh->SetupAttachment(_pCameraComponent);
	
	_pFPSMesh->bCastDynamicShadow = false;
	_pFPSMesh->CastShadow = false;

	//Stops the player from seeing their third person mesh
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AZombiePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using AZombiePlayerController"));
}

// Called every frame
void AZombiePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

// Called to bind functionality to input
void AZombiePlayerController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setup movement bindings
	PlayerInputComponent->BindAxis("MoveForward", this, &AZombiePlayerController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AZombiePlayerController::MoveRight);


	//Setup mouse look bindings
	//Using member method calls here to allow for additional processing such as mouse sensitivity in the future
	PlayerInputComponent->BindAxis("Turn", this, &AZombiePlayerController::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AZombiePlayerController::LookUp);


	//Setup action bindings
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AZombiePlayerController::StartJump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AZombiePlayerController::StopJump);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AZombiePlayerController::Fire);
}

void AZombiePlayerController::MoveForward(float value)
{
	//Figure out the forward vector for the player and move in that direction, based on scale (1 for W, -1 for S)
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, value);
}

void AZombiePlayerController::MoveRight(float value)
{
	//Figure out the right vector for the player and move in that direction, based on scale (1 for D, -1 for A)
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, value);
}

void AZombiePlayerController::Turn(float value)
{
	AddControllerYawInput(value);
}

void AZombiePlayerController::LookUp(float value)
{
	AddControllerPitchInput(value);
}

void AZombiePlayerController::StartJump()
{
	bPressedJump = true;
}

void AZombiePlayerController::StopJump()
{
	bPressedJump = false;
}

void AZombiePlayerController::Fire()
{
	if (!ProjectileClass) return;

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	//MuzzleOffset.Set(140.0f, 0.0f, 10.0f);

	//Transfrom the muzzle offset from camera space to world space
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
	
	FRotator MuzzleRotation = CameraRotation;
	//MuzzleRotation.Pitch += 10.0f;

	UWorld* World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		AZombieProjectile* pProjectile = World->SpawnActor<AZombieProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

		if (pProjectile) {
			FVector LaunchDirection = MuzzleRotation.Vector();
			pProjectile->FireInDirection(LaunchDirection);
		}
	}
}

