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
class UTFM_GameInstance;
class ATFM_WeaponBase;
class ATFM_BubbleBase;

UCLASS(config=Game)
class ATFM_G1Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

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


	UPROPERTY()
		UTFM_GameInstance* GameInstanceRef=nullptr;
	UFUNCTION()
		void LoadGameInstanceInfo();
	UFUNCTION()
		void SaveGameInstanceInfo();
protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> BaseStandardEmptyGun;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> HeavyGun;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> AnchorGun;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> AirGun;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> SoapGun;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		TSubclassOf<class ATFM_WeaponBase> MagneticGun;

	TMap<TSubclassOf<ATFM_BubbleBase>, TArray<ATFM_BubbleBase*>> SpawnedBubbles;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		class ATFM_WeaponBase* CurrentWeapon;

	int32 WeaponIndex;
	TArray<ATFM_WeaponBase*> WeaponArray;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool HeavyOn;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool AnchorOn;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool AirOn;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool SoapOn;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool MagneticOn;

protected:
	void SwitchNextWeapon();
	void SwitchPreviousWeapon();
	void CheckWeapons();

	/** Fires a projectile. */
	void OnFire();

	/** Fire Stops. */
	void OnFireStop();

	/** Fires Secondary. */
	void OnFireSecondary();

	/** Fires Stops Secondary. */
	void OnFireStopSecondary();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	void TurnAtRate(float Rate);

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
	virtual void Tick(float DeltaTime) override;

	bool IsHeavyEquiped() const;
	bool IsAnchorEquiped() const;
	bool IsAirEquiped() const;
	bool IsSoapEquiped() const;
	bool IsMagneticEquiped() const;

private:
	bool bHeavyEquiped = false;
	bool bAnchorEquiped = false;
	bool bAirEquiped = false;
	bool bSoapEquiped = false;
	bool bMagneticEquiped = false;
};

