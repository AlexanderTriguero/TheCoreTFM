// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_WeaponBase.generated.h"

class ATFM_BubbleBase;
class USphereComponent;

UCLASS()

class TFM_G1_API ATFM_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFM_WeaponBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
		USkeletalMeshComponent* SkeletalMesh = nullptr;
	//Sphere Collision to pick gun up if on the floor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
		USphereComponent* SphereCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* ProjectilePosition = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bubble Class")
		TSubclassOf<ATFM_BubbleBase> BubbleToSpawn = nullptr;
	float ChargePercent = 1.f;

protected:
	virtual void BeginPlay() override;
	virtual void Shoot();
	virtual void ShootSecondary();
	virtual void Reload();
};
