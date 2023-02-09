#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_WeaponObject.generated.h"

class UStaticMeshComponent;
class UTFM_BaseUserWidget;
class USphereComponent;
class UBoxComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		UBoxComponent* BoxCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<UTFM_BaseUserWidget> WidgetToOpen = nullptr;
	UPROPERTY()
		UTFM_BaseUserWidget* Widget = nullptr;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	UFUNCTION()
		void CloseTutorial(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* WeaponOnSound = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;
};
