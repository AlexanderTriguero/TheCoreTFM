// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapons/TFM_WeaponBase.h"
#include "TFM_AirGun.generated.h"

class UCapsuleComponent;
class UParticleSystemComponent;
UCLASS()
class TFM_G1_API ATFM_AirGun : public ATFM_WeaponBase
{
	GENERATED_BODY()

public:
	ATFM_AirGun();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void Shoot(ATFM_G1Character* CurrentCharacter) override;
	virtual void StopShooting(ATFM_G1Character* CurrentCharacter) override;
	virtual void ShootSecondary(ATFM_G1Character* CurrentCharacter) override;
	virtual void StopShootingSecondary() override;


private:
	int PushAttracValue = 1;
	bool bIsShooting = false;
	UAudioComponent* AudioComp = nullptr;
protected:
	UPROPERTY(EditAnywhere, Category="AirGun")
		UCapsuleComponent* VacuumCollision=nullptr;
	UPROPERTY(EditAnywhere, Category="AirGun")
		float Force= 3000000.f;
	UPROPERTY(EditAnywhere, Category = "Sound")
		USoundCue* AirSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Particles")
		UParticleSystemComponent* PushParticles = nullptr;
	UPROPERTY(EditAnywhere, Category = "Particles")
		UParticleSystemComponent* PullParticles = nullptr;
	

	
	UFUNCTION()
		void onEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
