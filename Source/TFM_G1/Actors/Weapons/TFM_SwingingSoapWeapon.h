// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bubbles/TFM_BubbleHeavy.h"
#include "Actors/Bubbles/TFM_BubbleAnchor.h"
#include "Actors/Weapons/TFM_WeaponBase.h"
#include "TFM_SwingingSoapWeapon.generated.h"

class ATFM_SwingingSoap;

UCLASS()
class TFM_G1_API ATFM_SwingingSoapWeapon : public ATFM_WeaponBase
{
	GENERATED_BODY()

public:
	virtual void Shoot() override;
	virtual void ShootSecondary() override;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ATFM_BubbleHeavy> BubbleToGrabOnto = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ATFM_BubbleHeavy> BubbleToReleaseTo = nullptr;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ATFM_SwingingSoap> SoapToSpawn = nullptr;

private:
	bool bSoapShot = false;
	ATFM_SwingingSoap* SoapSpawned = nullptr;
};
