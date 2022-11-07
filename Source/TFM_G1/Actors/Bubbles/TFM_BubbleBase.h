// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_BubbleBase.generated.h"

class UBoxComponent;
UENUM()
enum EBubbleSize
{
	NORMAL	UMETA(DisplayName = "Normal"),
	LARGE	UMETA(DisplayName = "Large"),
};

UCLASS()
class TFM_G1_API ATFM_BubbleBase : public AActor
{
	GENERATED_BODY()
public:	
	ATFM_BubbleBase();
	
	void Explode();
	void Resize(TEnumAsByte<EBubbleSize> NewSize);

protected:
	virtual void BeginPlay() override;
	TEnumAsByte<EBubbleSize> Size;

};
