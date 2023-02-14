// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/LevelObjects/TFM_TutorialCollider.h"
#include "TFM_Note.generated.h"

class UTFM_BaseUserWidget;
class UStaticMeshComponent;
UCLASS()
class TFM_G1_API ATFM_Note : public ATFM_TutorialCollider
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Note")
		UStaticMeshComponent* Mesh = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Note")
		TSubclassOf<UUserWidget> NoteContentClass = nullptr;
	UPROPERTY()
		UUserWidget* NoteContent = nullptr;

	ATFM_Note();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	
};
