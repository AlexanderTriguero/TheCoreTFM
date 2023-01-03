// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TFM_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TFM_G1_API UTFM_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
		int32 GetCurrentWeaponIndex();
	UFUNCTION()
		void SetCurrentWeaponIndex(int32 NewIndex);

	UFUNCTION()
		bool GetHeavyOn();
	UFUNCTION()
		void SetHeavyOn(bool NewHeavyOn);
	UFUNCTION()
		bool GetAnchorOn();
	UFUNCTION()
		void SetAnchorOn(bool NewAnchorOn);
	UFUNCTION()
		bool GetAirOn();
	UFUNCTION()
		void SetAirOn(bool NewAirOn);
	UFUNCTION()
		bool GetSoapOn();
	UFUNCTION()
		void SetSoapOn(bool NewSoapOn);
	UFUNCTION()
		bool GetMagneticOn();
	UFUNCTION()
		void SetMagneticOn(bool NewMagneticOn);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bHeavyOn = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bAnchorOn = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bAirOn = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bSoapOn = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bMagneticOn = false;
private:
	int32 CurrentWeaponIndex = 0;
	
};
