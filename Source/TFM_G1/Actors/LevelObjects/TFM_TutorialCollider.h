// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TFM_TutorialCollider.generated.h"

class UBoxComponent;
class UTFM_BaseUserWidget;
class ATFM_G1Character;
UCLASS()
class TFM_G1_API ATFM_TutorialCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATFM_TutorialCollider();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		UBoxComponent* BoxCollider = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		TSubclassOf<UTFM_BaseUserWidget> WidgetToOpen = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bHeavyRequired = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bAnchorRequired = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bAirRequired = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bSoapRequired = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		bool bElectricRequired = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget")
		bool ShowAtStart = false;


	UPROPERTY()
		UTFM_BaseUserWidget* Widget = nullptr;

	UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bActivable = true;
	bool bWidgetShowed = false;

	bool RequirementsSatisfied(AActor* OtherActor);


};
