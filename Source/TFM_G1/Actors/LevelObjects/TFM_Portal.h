// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelObjects/TFM_EndOfLevel.h"
#include "TFM_Portal.generated.h"

/**
 * 
 */

class UStaticMeshComponent;
class UParticleSystemComponent;
UCLASS()
class TFM_G1_API ATFM_Portal : public ATFM_EndOfLevel
{
	GENERATED_BODY()

public:
	ATFM_Portal();

	UPROPERTY(EditAnywhere, Category = "Portal")
		UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Portal")
		UParticleSystemComponent* ParticleSystem = nullptr;
	
};
