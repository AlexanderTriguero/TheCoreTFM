// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/TFM_WeaponBase.h"
#include "TFM_AirGun.generated.h"

class UCapsuleComponent;
UCLASS()
class TFM_G1_API ATFM_AirGun : public ATFM_WeaponBase
{
	GENERATED_BODY()

public:
	ATFM_AirGun();
	virtual void Tick(float DeltaTime) override;

private:
	int PushAttracValue = 1;
	bool bIsShooting = false;
protected:
	UPROPERTY(EditAnywhere, Category="AirGun")
		UCapsuleComponent* VacuumCollision=nullptr;

	UPROPERTY(EditAnywhere, Category="AirGun")
		float Force=10000;

	virtual void BeginPlay() override;
	virtual void Shoot() override;
	virtual void ShootSecondary() override;

	virtual void StopShooting();

};
