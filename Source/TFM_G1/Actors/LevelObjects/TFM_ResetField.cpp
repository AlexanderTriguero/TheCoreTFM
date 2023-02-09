// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_ResetField.h"

#include "TFM_G1Character.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Components/BoxComponent.h"
#include "Actors/Weapons/TFM_WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/TFM_WeaponWidget.h"

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
	if(ATFM_G1Character* GameCharacter = Cast<ATFM_G1Character>(OtherActor))
	{
		if(ResetSound)
			UGameplayStatics::PlaySoundAtLocation(this, ResetSound, GetActorLocation());
		for (AActor* Actor : OverlappingActors)
		{
			if (ATFM_BubbleBase* Bubble = Cast<ATFM_BubbleBase>(Actor))
			{
				if (!Bubble->bLevelAsset)
				{
					GameCharacter->SpawnedBubbles.Find(Bubble->GetClass())->Remove(Bubble);
					if (ATFM_WeaponBase* Weapon = Cast<ATFM_WeaponBase>(Bubble->GetOwner()))
					{
						Weapon->GetWidget()->DeleteBubble();
					}
					Bubble->Destroy();
				}
			}
		}
	}
}

