// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/TFM_ActorBase.h"
#include "TFM_BubbleBase.generated.h"

class UBoxComponent;
UENUM()
enum EBubbleSize
{
	NORMAL	UMETA(DisplayName = "Normal"),
	LARGE	UMETA(DisplayName = "Large"),
};

UCLASS()
class TFM_G1_API ATFM_BubbleBase : public ATFM_ActorBase
{
	GENERATED_BODY()
public:	
	ATFM_BubbleBase();
	virtual void ApplyForce(FVector Direction, float Force, int PushAttracValue) override;
	void Explode();
	void Resize(TEnumAsByte<EBubbleSize> NewSize);

protected:
	TEnumAsByte<EBubbleSize> Size;
	//Collider para detectar que hay una burbuja encima, de está manera, al explotar se pueden añadir fisicas al objeto que tiene encima, para que este caiga
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anchor")
		UBoxComponent* TopDetection = nullptr;

	virtual void BeginPlay() override;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
