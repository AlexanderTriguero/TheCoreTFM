// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_ResetField.h"

#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Components/BoxComponent.h"

ATFM_ResetField::ATFM_ResetField()
{
	ResetArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Reset Area"));
	ResetArea->SetupAttachment(Mesh);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &ATFM_ResetField::OnComponentEndOverlapOnField);
}

void ATFM_ResetField::OnComponentEndOverlapOnField(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> OverlappingActors;
	ResetArea->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (ATFM_BubbleBase* Bubble = Cast<ATFM_BubbleBase>(Actor))
		{
			if (!Bubble->bLevelAsset)
				Bubble->Destroy();
		}
	}
}

