// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/TFM_ActorBase.h"
#include "TFM_PowerSource.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class TFM_G1_API ATFM_PowerSource : public ATFM_ActorBase
{
	GENERATED_BODY()

public:
	ATFM_PowerSource();
	UPROPERTY(EditAnywhere)
		float ConnectionRadius;
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* ConnectionSphere = nullptr;
	UPROPERTY(EditAnywhere)
		USceneComponent* ConnectionPoint = nullptr;
	UFUNCTION()
		void OnComponentEndOverlapOnPowerSource(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

};
