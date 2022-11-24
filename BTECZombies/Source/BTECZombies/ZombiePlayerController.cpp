// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiePlayerController.h"
#include "Camera/CameraComponent.h"

#include "ZombieWindow.h"
#include "BTECZombiesGameModeBase.h"

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

	_currentHealth = _maxHealth;

	AZombieWeapon* weapon = GetWorld()->SpawnActor<AZombieWeapon>(_StartingWeapon);
	if (weapon) {
		EquipWeapon(weapon);
		_CurrentWeapon = _PrimaryWeapon;
	}
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
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AZombiePlayerController::Interact);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &AZombiePlayerController::Reload);
	PlayerInputComponent->BindAction("MouseWheelUp", EInputEvent::IE_Pressed, this, &AZombiePlayerController::MouseWheelUp);
	PlayerInputComponent->BindAction("MouseWheelDown", EInputEvent::IE_Pressed, this, &AZombiePlayerController::MouseWheelDown);

}

float AZombiePlayerController::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float dam = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (_isDead) return 0.0f;

	_currentHealth -= dam;

	UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), _currentHealth);

	if (_currentHealth <= 0.0f) {
		_isDead = true;
		UE_LOG(LogTemp, Warning, TEXT("Player Dead"));

		ABTECZombiesGameModeBase* gb = Cast<ABTECZombiesGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gb) {
			gb->PlayerKilled(this);
		}
	}

	return dam;
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
	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(140.0f, 0.0f, 0.0f);

	//Transfrom the muzzle offset from camera space to world space
	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	_CurrentWeapon->PullTrigger(MuzzleLocation, CameraRotation);

	
}

void AZombiePlayerController::Interact()
{
	if (_NearbyWindow && !_NearbyWindow->IsBlocked()) {
		ABTECZombiesGameModeBase* gm = Cast<ABTECZombiesGameModeBase>(GetWorld()->GetAuthGameMode());
		if (gm) {
			if (gm->GetCurrentPoints() >= _NearbyWindow->GetPointsToOpen()) {
				gm->SpendPoints(_NearbyWindow->GetPointsToOpen());
				_NearbyWindow->BoardUpWindow();
			}
		}
	}

	if (_NearbyWeaponToPickup) {
		//TODO: Can afford to pickup

		AZombieWeapon* weapon = GetWorld()->SpawnActor<AZombieWeapon>(_NearbyWeaponToPickup->GetWeaponToSpawn());
		EquipWeapon(weapon);

		_NearbyWeaponToPickup->Destroy();
		_NearbyWeaponToPickup = nullptr;
	}
}

void AZombiePlayerController::Reload()
{
	if (_CurrentWeapon) {
		_CurrentWeapon->StartReload();
	}
}

void AZombiePlayerController::MouseWheelUp()
{
	if (_SecondaryWeapon == nullptr) return;

	if (_CurrentWeapon == _PrimaryWeapon) {
		_PrimaryWeapon->Hide(true);
		_CurrentWeapon = _SecondaryWeapon;
		_SecondaryWeapon->Hide(false);
	}
	else {
		_SecondaryWeapon->Hide(true);
		_CurrentWeapon = _PrimaryWeapon;
		_PrimaryWeapon->Hide(false);
	}
}

void AZombiePlayerController::MouseWheelDown()
{
	if (_SecondaryWeapon == nullptr) return;

	if (_CurrentWeapon == _PrimaryWeapon) {
		_PrimaryWeapon->Hide(true);
		_CurrentWeapon = _SecondaryWeapon;
		_SecondaryWeapon->Hide(false);
	}
	else {
		_SecondaryWeapon->Hide(true);
		_CurrentWeapon = _PrimaryWeapon;
		_PrimaryWeapon->Hide(false);
	}
}

FString AZombiePlayerController::GetInteractPrompt() {
	if (_NearbyWindow != nullptr && !_NearbyWindow->IsBlocked()) {
		return FString(TEXT("Press E to Board Up Window: ")) + FString::FromInt(_NearbyWindow->GetPointsToOpen());
	}
	return FString(TEXT(""));
}

void AZombiePlayerController::EquipWeapon(AZombieWeapon* Weapon)
{
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);

	Weapon->AttachToComponent(_pFPSMesh, rules, "s_LeftHand");
	Weapon->Init(GetController());

	if (_PrimaryWeapon == nullptr) {
		_PrimaryWeapon = Weapon;
		return;
	}

	if (_SecondaryWeapon == nullptr) {
		_SecondaryWeapon = Weapon;
		return;
	}

	//TODO: handle swapping weapon logic
	_CurrentWeapon = Weapon;
}

