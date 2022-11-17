// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TFM_SkeletalActor.h"
#include "LevelObjects/TFM_SwitchFloor.h"

// Sets default values
ATFM_SkeletalActor::ATFM_SkeletalActor()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(RootComponent);

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
		Mesh->PlayAnimation(AnimStateOpen, false);
	}
}

void ATFM_SkeletalActor::Deactivate()
{
	if (bIsSwitchable)
	{
		bIsActive = false;
		Mesh->PlayAnimation(AnimStateClose, false);
	}
}
