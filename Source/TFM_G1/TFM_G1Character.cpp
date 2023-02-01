// Copyright Epic Games, Inc. All Rights Reserved.

#include "TFM_G1Character.h"
#include "TFM_G1Projectile.h"
#include "Animation/AnimInstance.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId
#include "GameInstances/TFM_GameInstance.h"


DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATFM_G1Character

ATFM_G1Character::ATFM_G1Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	//FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	//FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	//FP_Gun->bCastDynamicShadow = false;
	//FP_Gun->CastShadow = false;
	//// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	//FP_Gun->SetupAttachment(RootComponent);

	//FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	//FP_MuzzleLocation->SetupAttachment(FP_Gun);
	//FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	//// Default offset from the character location for projectiles to spawn
	//GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.


	//

	WeaponIndex = 0;

}

void ATFM_G1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(WeaponArray.Num()==0)
		Mesh1P->SetHiddenInGame(true);

	CheckWeapons();
}

void ATFM_G1Character::BeginPlay()
{
	Super::BeginPlay();

	if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(BaseStandardEmptyGun)) 
	{
		CurrentWeapon = Weapon;
	}

	/*
	if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(HeavyGun))
	{  //SUPONIENDO QUE LA PRIMERA SIEMPRE SER� HEAVYGUN
		Weapon->isOnCharacter = HeavyOn;
		CurrentWeapon = Weapon;
		if (!HeavyOn) 
		{
			CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(true);
		}
		WeaponArray.Add(CurrentWeapon);
		CurrentWeapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	}
	if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(AnchorGun))
	{
		Weapon->isOnCharacter = AnchorOn;
		Weapon->GetWeaponMesh()->SetHiddenInGame(true);
		WeaponArray.Add(Weapon);
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	}
	if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(AirGun))
	{
		Weapon->isOnCharacter = AirOn;
		Weapon->GetWeaponMesh()->SetHiddenInGame(true);
		WeaponArray.Add(Weapon);
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	}
	if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(SoapGun))
	{
		Weapon->isOnCharacter = SoapOn;
		Weapon->GetWeaponMesh()->SetHiddenInGame(true);
		WeaponArray.Add(Weapon);
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	}
	*/
	/*if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(FourthWeaponClass))
	{
		Weapon->GetWeaponMesh()->SetHiddenInGame(true);
		WeaponArray.Add(Weapon);
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	}
	if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(FifthWeaponClass))
	{
		Weapon->GetWeaponMesh()->SetHiddenInGame(true);
		WeaponArray.Add(Weapon);
		Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));
	}*/

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	//FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));


	GameInstanceRef=Cast<UTFM_GameInstance>(GetWorld()->GetGameInstance());
	LoadGameInstanceInfo();

	/*if (CurrentWeapon)
	{
		if (ATFM_WeaponBase* NextWeapon = WeaponArray[WeaponIndex])
		{
			CurrentWeapon->HideSpawnPreview();
			CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(true);
			CurrentWeapon = NextWeapon;
			CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
		}
	}*/
}

void ATFM_G1Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATFM_G1Character::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATFM_G1Character::OnFireStop);

	// Bind fire2 event
	PlayerInputComponent->BindAction("Fire2", IE_Pressed, this, &ATFM_G1Character::OnFireSecondary);
	PlayerInputComponent->BindAction("Fire2", IE_Released, this, &ATFM_G1Character::OnFireStopSecondary);

	// Bind chage weapon event
	PlayerInputComponent->BindAction("SwitchNextWeapon", IE_Pressed, this, &ATFM_G1Character::SwitchNextWeapon);
	PlayerInputComponent->BindAction("SwitchPreviousWeapon", IE_Pressed, this, &ATFM_G1Character::SwitchPreviousWeapon);

	// Bind pause game event
	PlayerInputComponent->BindAction("PauseGame", IE_Released, this, &ATFM_G1Character::PauseGame);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATFM_G1Character::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATFM_G1Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATFM_G1Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATFM_G1Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATFM_G1Character::LookUpAtRate);
}

void ATFM_G1Character::OnFire()
{
	if (!CurrentWeapon->isOnCharacter)
		return;

	CurrentWeapon->Shoot(this);
}

void ATFM_G1Character::OnFireStop()
{
	if (!CurrentWeapon->isOnCharacter)
		return;

	CurrentWeapon->StopShooting(this);
}

void ATFM_G1Character::OnFireSecondary()
{
	if (!CurrentWeapon->isOnCharacter)
		return;

	CurrentWeapon->ShootSecondary(this);
}

void ATFM_G1Character::OnFireStopSecondary()
{
	CurrentWeapon->StopShootingSecondary();
}

void ATFM_G1Character::PauseGame()
{
	if (PauseWidgetClass)
	{
		if (!PauseWidget)
		{
			PauseWidget = CreateWidget(GetWorld(), PauseWidgetClass);
			PauseWidget->AddToViewport();
		}
		else
		{
			PauseWidget->SetVisibility(ESlateVisibility::Visible);
		}
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		PC->Pause();
	}
	
}


void ATFM_G1Character::SwitchNextWeapon()
{
	if (CurrentWeapon)
	{
		if (WeaponArray.Num() > WeaponIndex + 1)
		{
			++WeaponIndex;
			if (ATFM_WeaponBase* NextWeapon = WeaponArray[WeaponIndex]) 
			{
				if(NextWeapon->isOnCharacter)
				{
					CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(true);
					CurrentWeapon = NextWeapon;
					CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				}
				CurrentWeapon->HideSpawnPreview();
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(true);
				CurrentWeapon = NextWeapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
			}
		}
	}
}

void ATFM_G1Character::SwitchPreviousWeapon()
{
	if (CurrentWeapon && CurrentWeapon->isOnCharacter)
	{
		if (WeaponIndex - 1 >= 0)
		{
			--WeaponIndex;
			if (ATFM_WeaponBase* NextWeapon = WeaponArray[WeaponIndex])
			{
				if (NextWeapon->isOnCharacter) 
				{
					CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(true);
					CurrentWeapon = NextWeapon;
					CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				}
			}
		}
	}

}

void ATFM_G1Character::CheckWeapons()
{
	if (HeavyOn && !bHeavyEquiped)
	{
		if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(HeavyGun))
		{
			Weapon->isOnCharacter = HeavyOn;
			Weapon->GetWeaponMesh()->SetHiddenInGame(true);
			WeaponArray.Add(Weapon);
			Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));

			if (WeaponArray.Num() == 1)
			{
				CurrentWeapon = Weapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				Mesh1P->SetHiddenInGame(false);
			}
			HeavyOn = false;
			bHeavyEquiped = true;
		}

	}
	if (AnchorOn && !bAnchorEquiped)
	{
		if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(AnchorGun))
		{
			Weapon->isOnCharacter = AnchorOn;
			Weapon->GetWeaponMesh()->SetHiddenInGame(true);
			WeaponArray.Add(Weapon);
			Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));

			if (WeaponArray.Num() == 1)
			{
				CurrentWeapon = Weapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				Mesh1P->SetHiddenInGame(false);
			}

			AnchorOn = false;
			bAnchorEquiped = true;
		}

	}
	if (AirOn && !bAirEquiped)
	{
		if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(AirGun))
		{
			Weapon->isOnCharacter = AirOn;
			Weapon->GetWeaponMesh()->SetHiddenInGame(true);
			WeaponArray.Add(Weapon);
			Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));

			if (WeaponArray.Num() == 1)
			{
				CurrentWeapon = Weapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				Mesh1P->SetHiddenInGame(false);
			}

			AirOn = false;
			bAirEquiped = true;
		}

	}
	if (SoapOn && !bSoapEquiped)
	{
		if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(SoapGun))
		{
			Weapon->isOnCharacter = SoapOn;
			Weapon->GetWeaponMesh()->SetHiddenInGame(true);
			WeaponArray.Add(Weapon);
			Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));

			if (WeaponArray.Num() == 1)
			{
				CurrentWeapon = Weapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				Mesh1P->SetHiddenInGame(false);
			}
			SoapOn = false;
			bSoapEquiped = true;
		}

	}

	if (MagneticOn && !bMagneticEquiped)
	{
		if (ATFM_WeaponBase* Weapon = GetWorld()->SpawnActor<ATFM_WeaponBase>(MagneticGun))
		{
			Weapon->isOnCharacter = MagneticOn;
			Weapon->GetWeaponMesh()->SetHiddenInGame(true);
			WeaponArray.Add(Weapon);
			Weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("GripPoint"));

			if (WeaponArray.Num() == 1)
			{
				CurrentWeapon = Weapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
				Mesh1P->SetHiddenInGame(false);
			}
			MagneticOn = false;
			bMagneticEquiped = true;
		}

	}
}

void ATFM_G1Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATFM_G1Character::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ATFM_G1Character::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void ATFM_G1Character::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATFM_G1Character::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATFM_G1Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATFM_G1Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ATFM_G1Character::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATFM_G1Character::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ATFM_G1Character::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATFM_G1Character::TouchUpdate);
		return true;
	}
	
	return false;
}

void ATFM_G1Character::LoadGameInstanceInfo() {
	WeaponIndex=GameInstanceRef->GetCurrentWeaponIndex();
	HeavyOn = GameInstanceRef->GetHeavyOn();
	AnchorOn = GameInstanceRef->GetAnchorOn();
	AirOn = GameInstanceRef->GetAirOn();
	SoapOn = GameInstanceRef->GetSoapOn();
	MagneticOn = GameInstanceRef->GetMagneticOn();
	CheckWeapons();
	if (WeaponArray.Num()>0) {
		if (ATFM_WeaponBase* NextWeapon = WeaponArray[WeaponIndex])
		{
			if (NextWeapon->isOnCharacter)
			{
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(true);
				CurrentWeapon = NextWeapon;
				CurrentWeapon->GetWeaponMesh()->SetHiddenInGame(false);
			}
		}
	}
}
void ATFM_G1Character::SaveGameInstanceInfo() {
	GameInstanceRef->SetCurrentWeaponIndex(WeaponIndex);
	GameInstanceRef->SetHeavyOn(bHeavyEquiped);
	GameInstanceRef->SetAnchorOn(bAnchorEquiped);
	GameInstanceRef->SetAirOn(bAirEquiped);
	GameInstanceRef->SetSoapOn(bSoapEquiped);
	GameInstanceRef->SetMagneticOn(bMagneticEquiped);


}

bool ATFM_G1Character::IsHeavyEquiped() const
{
	return bHeavyEquiped;
}
bool ATFM_G1Character::IsAnchorEquiped() const
{
	return bAnchorEquiped;
}
bool ATFM_G1Character::IsAirEquiped() const
{
	return bAirEquiped;
}
bool ATFM_G1Character::IsSoapEquiped() const
{
	return bSoapEquiped;
}
bool ATFM_G1Character::IsMagneticEquiped() const
{
	return bMagneticEquiped;
}

