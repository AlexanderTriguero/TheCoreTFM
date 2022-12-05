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

	/*No hace falta implementarlo si no se van a modificar las f�sicas
	virtual void Tick(float DeltaTime) override;*/
	virtual void ApplyForce(FVector Direction, float Force, int PushAttracValue) override;
	void Explode();
	void Resize(TEnumAsByte<EBubbleSize> NewSize);
	UFUNCTION()
		FVector GetPointToSpawn();
	UFUNCTION()
		bool HasSomethingOnTop();

protected:
	TEnumAsByte<EBubbleSize> Size;
	//Collider para detectar que hay una burbuja encima, de est� manera, al explotar se pueden a�adir fisicas al objeto que tiene encima, para que este caiga
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anchor")
		UBoxComponent* TopDetection = nullptr;

	virtual void BeginPlay() override;
	/* Metodos para manejar fisicas
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	*/
};
