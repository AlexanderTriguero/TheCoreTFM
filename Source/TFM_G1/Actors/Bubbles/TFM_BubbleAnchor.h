// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "TFM_BubbleAnchor.generated.h"

class UBoxComponent;
class ATFM_BubbleHeavy;
UCLASS()
class TFM_G1_API ATFM_BubbleAnchor : public ATFM_BubbleBase
{
	GENERATED_BODY()
	
public:
	ATFM_BubbleAnchor();

	virtual void ApplyForce(FVector Direction, float Force, int PushAttracValue) override;
	virtual void EnablePhysics() override;
	virtual void DisablePhysics() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anchor")
		UBoxComponent* BoxCollider = nullptr;

	virtual void BeginPlay() override;

};
