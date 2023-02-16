// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleHeavy.h"

#include "Actors/LevelObjects/TFM_SwitchFloor.h"
#include "Components/BoxComponent.h"

ATFM_BubbleHeavy::ATFM_BubbleHeavy() : Super()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxCollider->SetupAttachment(Mesh);
	OnDestroyed.AddDynamic(this, &ATFM_BubbleHeavy::NotifyDestruction);
}

void ATFM_BubbleHeavy::NotifyDestruction(AActor* DestroyedActor)
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_SwitchFloor::StaticClass());
	for (AActor* Actor : Result)
	{
		if (ATFM_SwitchFloor* Switch = Cast<ATFM_SwitchFloor>(Actor))
		{
			if (Switch->IsActive)
			{
				Switch->DeactivateButton();
			}
		}
	}
}

