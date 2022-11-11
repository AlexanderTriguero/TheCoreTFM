// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "TFM_BubbleAnchor.generated.h"

class UBoxComponent;
UCLASS()
class TFM_G1_API ATFM_BubbleAnchor : public ATFM_BubbleBase
{
	GENERATED_BODY()
	
public:
	ATFM_BubbleAnchor();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collider")
		UBoxComponent* BoxCollider = nullptr;
};
