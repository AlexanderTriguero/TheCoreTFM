#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_WeaponObject.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class TFM_G1_API ATFM_WeaponObject : public AActor
{
	GENERATED_BODY()
	
public:	
	ATFM_WeaponObject();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bubble Weapons")
		UStaticMeshComponent* WeaponMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		USphereComponent* PickRadius = nullptr;

	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool HeavyOnPickUp;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool AnchorOnPickUp;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool AirOnPickUp;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool SoapOnPickUp;
	UPROPERTY(EditAnywhere, Category = "Bubble Weapons")
		bool MagneticOnPickUp;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};