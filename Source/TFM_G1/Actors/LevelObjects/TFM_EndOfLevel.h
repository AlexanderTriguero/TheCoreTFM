// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_EndOfLevel.generated.h"

class UBoxComponent;

UCLASS()
class TFM_G1_API ATFM_EndOfLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATFM_EndOfLevel();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "End Of Level")
	FName LevelToLoad;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "End Of Level")
		UBoxComponent* BoxCollider = nullptr;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
