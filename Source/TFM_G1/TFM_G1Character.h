// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Actors/Weapons/TFM_WeaponBase.h"
#include "TFM_G1Character.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UAnimMontage;
class USoundBase;

class ATFM_WeaponBase;

UCLASS(config=Game)
class ATFM_G1Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* L_MotionController;

public:
	ATFM_G1Character();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	//FVector GunOffset;

	/** Projectile class to spawn */
	//UPROPERTY(EditDefaultsOnly, Category=Projectile)
	//TSubclassOf<class ATFM_G1Projectile> ProjectileClass;

	/** AnimMontage to play each time we fire */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	//UAnimMontage* FireAnimation;

	//
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> StartingWeaponClass;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> SecondWeaponClass;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> ThirdWeaponClass;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> FourthWeaponClass;


	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		class ATFM_WeaponBase* CurrentWeapon;

	int32 WeaponIndex;
	TArray<ATFM_WeaponBase*> WeaponArray;

protected:
	void SwitchNextWeapon();
	void SwitchPreviousWeapon();

	/** Fires a projectile. */
	void OnFire();

	/** Fire Stops. */
	void OnFireStop();

	/** Fires Secondary. */
	void OnFireSecondary();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

