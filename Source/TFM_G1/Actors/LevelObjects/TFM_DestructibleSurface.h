// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_DestructibleSurface.generated.h"

class UBoxComponent;

UCLASS()
class TFM_G1_API ATFM_DestructibleSurface : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Category = "Surface")
		float DestroySpeed = 1000.f;
	ATFM_DestructibleSurface();
	virtual void Tick(float DeltaTime) override;
	void DestroySelf();
protected:
	UPROPERTY(EditAnywhere, Category = "DestructibleSurface")
		UStaticMeshComponent* Mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DestructibleSurface")
		UBoxComponent* BoxCollider = nullptr;

	virtual void BeginPlay() override;
	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



};
