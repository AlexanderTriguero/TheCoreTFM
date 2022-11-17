// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/TFM_WeaponBase.h"
#include "TFM_AnchorWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TFM_G1_API ATFM_AnchorWeapon : public ATFM_WeaponBase
{
	GENERATED_BODY()

public:
	virtual void ShootSecondary() override;

};
