// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/TFM_ActorBase.h"
#include "TFM_ResetField.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class TFM_G1_API ATFM_ResetField : public ATFM_ActorBase
{
	GENERATED_BODY()

	ATFM_ResetField();

public:
	UPROPERTY(EditAnywhere)
		UBoxComponent* ResetArea = nullptr;
	UFUNCTION()
		void OnComponentEndOverlapOnField(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
		USoundBase* ResetSound = nullptr;
};
