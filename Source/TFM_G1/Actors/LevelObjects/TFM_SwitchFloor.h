// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/TFM_ActorBase.h"
#include "TFM_SwitchFloor.generated.h"

class ATFM_SkeletalActor;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class TFM_G1_API ATFM_SwitchFloor : public ATFM_ActorBase
{
	GENERATED_BODY()

public:
	ATFM_SwitchFloor();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collider")
		UBoxComponent* BoxCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collider")
		bool IsActive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Related Objects")
		TArray<ATFM_SkeletalActor*> RelatedActors;
	UFUNCTION()
		void OnComponentBeginOverlapOnSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlapOnSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
		void ActivateButton();
	UFUNCTION(BlueprintCallable)
		void DeactivateButton();
};
