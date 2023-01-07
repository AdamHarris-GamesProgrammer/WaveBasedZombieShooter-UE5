// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiePlayerController.h"
#include "Camera/CameraComponent.h"

#include "ZombieWindow.h"
#include "ZombieDoor.h"
#include "ZombieWeapon.h"
#include "WeaponSpawnPoint.h"
#include "Components/CapsuleComponent.h"
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

	for (int i = 0; i < (int)AmmoType::AmmoTypeSize; ++i) {
		_AmmoStore.Add(60);
	}

	AZombieWeapon* weapon = GetWorld()->SpawnActor<AZombieWeapon>(_StartingWeapon);
	if (weapon) {
		EquipWeapon(weapon);
		_CurrentWeapon = _PrimaryWeapon;
		_CurrentWeapon->Hide(false);
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
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AZombiePlayerController::StopFiring);

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

	//UE_LOG(LogTemp, Warning, TEXT("Player Health: %f"), _currentHealth);

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
	if (_CurrentWeapon != nullptr) {
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		_CurrentWeapon->StartFiring();
	}
}

void AZombiePlayerController::StopFiring()
{
	if (_CurrentWeapon != nullptr) {
		_CurrentWeapon->EndFiring();
	}
}

void AZombiePlayerController::Interact()
{
	ABTECZombiesGameModeBase* gm = Cast<ABTECZombiesGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!gm) return;

	if (_NearbyWindow && !_NearbyWindow->IsBlocked()) {
		if (gm->CanAfford(_NearbyWindow->GetBlockCost())) {
			gm->SpendPoints(_NearbyWindow->GetBlockCost());
			_NearbyWindow->BoardUpWindow();
		}
	}

	if (_NearbyWeaponToPickup) {
		//TODO: Can afford to pickup

		if (gm->CanAfford(_NearbyWeaponToPickup->GetPickupCost())) {
			AZombieWeapon* weapon = GetWorld()->SpawnActor<AZombieWeapon>(_NearbyWeaponToPickup->GetWeaponToSpawn());
			EquipWeapon(weapon);

			gm->SpendPoints(_NearbyWeaponToPickup->GetPickupCost());
			_NearbyWeaponToPickup->DespawnMesh();
			_NearbyWeaponToPickup->Destroy();
			_NearbyWeaponToPickup = nullptr;
		}
	}

	if (_NearbyDoor) {
		if (gm->CanAfford(_NearbyDoor->GetCostToOpen())) {
			_NearbyDoor->OpenDoor();

			gm->SpendPoints(_NearbyDoor->GetCostToOpen());
		}
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
	if (_CurrentWeapon->IsReloading()) return;
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
	if (_CurrentWeapon->IsReloading()) return;
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
		return FString(TEXT("Press E to Board Up Window: ")) + FString::FromInt(_NearbyWindow->GetBlockCost());
	}

	if (_NearbyWeaponToPickup != nullptr) {
		return FString(TEXT("Press E to Pickup Weapon: ")) + FString::FromInt(_NearbyWeaponToPickup->GetPickupCost());
	}

	if (_NearbyDoor != nullptr && !_NearbyDoor->IsOpen()) {
		return FString(TEXT("Press E to Open Door: ")) + FString::FromInt(_NearbyDoor->GetCostToOpen());
	}

	return FString(TEXT(""));
}

void AZombiePlayerController::EquipWeapon(AZombieWeapon* Weapon)
{
	FAttachmentTransformRules rules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);

	Weapon->AttachToComponent(_pFPSMesh, rules, "s_LeftHand");
	Weapon->Init(GetController(), this);
	Weapon->Hide(true);

	if (_PrimaryWeapon == nullptr) {
		_PrimaryWeapon = Weapon;
		return;
	}

	if (_SecondaryWeapon == nullptr) {
		_SecondaryWeapon = Weapon;
		return;
	}
}

void AZombiePlayerController::AddRoom(AZombieRoom* room) {

	_CurrentRoom = room;
	UE_LOG(LogTemp, Warning, TEXT("Set Room"));

	_PastRooms.Insert(room, 0);

	if (_PastRooms.Num() > 3) {
		_PastRooms.RemoveAt(3);
	}


	UE_LOG(LogTemp, Warning, TEXT("Rooms Array contains"));
	for (auto* r : _PastRooms) {
		UE_LOG(LogTemp, Warning, TEXT("Room Name: %s"), *r->GetName());
	}

}

bool AZombiePlayerController::HasAmmo(AmmoType type) const
{
	return _AmmoStore[(int)type] > 0;
}

int AZombiePlayerController::ConsumeAmmo(AmmoType type, int amount)
{
	int bullets = _AmmoStore[(int)type];

	//If we are requesting more ammo than we have
	if (bullets < amount) {
		_AmmoStore[(int)type] = 0;
		return bullets;
	}

	//If we have more ammo than what we are requesting
	if (bullets >= amount) {
		_AmmoStore[(int)type] -= amount;
		return amount;
	}

	return 0;
}

void AZombiePlayerController::GainAmmo(AmmoType type, int amount)
{
	_AmmoStore[(int)type] += amount;
}

