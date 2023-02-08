// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_WeaponBase.generated.h"

class USoundCue;
class ATFM_G1Character;
class ATFM_BubbleBase;
class USphereComponent;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()

class TFM_G1_API ATFM_WeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
		USkeletalMeshComponent* WeaponMesh = nullptr;
	//Sphere Collision to pick gun up if on the floor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Properties")
		USphereComponent* SphereCollision = nullptr;
	UPROPERTY(EditDefaultsOnly)
		USceneComponent* ProjectilePosition = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bubble Class")
		TSubclassOf<ATFM_BubbleBase> BubbleToSpawn = nullptr;
	float ChargePercent = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bubble Class")
		bool isOnCharacter;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Preview")
		UStaticMeshComponent* PositionToSpawnBubble = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Preview")
		UMaterialInterface* CanSpawnMaterial= nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Preview")
		UMaterialInterface* CanNotSpawnMaterial=nullptr;


	ATFM_WeaponBase();
	class USkeletalMeshComponent* GetWeaponMesh() { return WeaponMesh; }
	virtual void Tick(float DeltaTime) override;
	virtual void Shoot(ATFM_G1Character* CurrentCharacter);
	virtual void StopShooting(ATFM_G1Character* CurrentCharacter);
	virtual void ShootSecondary(ATFM_G1Character* CurrentCharacter);
	virtual void StopShootingSecondary();
	virtual void Reload();
	virtual void HideSpawnPreview();

protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* ShotAudio = nullptr;
	UPROPERTY(EditAnywhere, Category = "Audio")
		class USoundBase* SecondaryShotAudio = nullptr;


	UPROPERTY(EditAnywhere, Category = "Weapon")
		int MaxSpawnedBubbles=4;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		int BubbleDestroyDistance = 1500;
	virtual void BeginPlay() override;
	virtual void CheckIfCanSpawnBubble();

private:
	bool bSpawningBubble = false;
	bool bCanSpawnBubble = false;

};
