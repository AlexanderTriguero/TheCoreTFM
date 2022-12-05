// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TFM_SkeletalActor.h"
#include "LevelObjects/TFM_SwitchFloor.h"

// Sets default values
ATFM_SkeletalActor::ATFM_SkeletalActor()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Frame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	Frame->SetupAttachment(RootComponent);
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(Frame);

}

void ATFM_SkeletalActor::TryActivate()
{
	if (SwitchList.Num() > 0)
	{
		for (ATFM_SwitchFloor* Switch : SwitchList)
		{
			if (Switch->IsActive)
			{
				continue;
			}
			return;
		}
		Activate();
	}
}

void ATFM_SkeletalActor::Activate()
{
	if (bIsSwitchable)
	{
		bIsActive = true;
		Door->SetHiddenInGame(true);
		Door->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Mesh->PlayAnimation(AnimStateOpen, false);
	}
}

void ATFM_SkeletalActor::Deactivate()
{
	if (bIsSwitchable)
	{
		bIsActive = false;
		Door->SetHiddenInGame(false);
		Door->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		//Mesh->PlayAnimation(AnimStateClose, false);
	}
}
