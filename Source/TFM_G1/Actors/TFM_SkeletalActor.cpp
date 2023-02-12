// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TFM_SkeletalActor.h"

#include "Bubbles/TFM_BubbleElectric.h"
#include "Kismet/GameplayStatics.h"
#include "LevelObjects/TFM_SwitchFloor.h"

// Sets default values
ATFM_SkeletalActor::ATFM_SkeletalActor()
{
	PrimaryActorTick.bCanEverTick = true;
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
	if (bIsSwitchable || bIsElectric)
	{
		if (DoorOpenSound)
			UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, GetActorLocation());
		bIsActive = true;
		Door->SetHiddenInGame(true);
		Door->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//Mesh->PlayAnimation(AnimStateOpen, false);
	}
}

void ATFM_SkeletalActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsElectric) {

		Deactivate();
	}
}

bool ATFM_SkeletalActor::IsConnected()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_BubbleElectric::StaticClass());
	for (AActor* Actor : Result)
	{
		if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(Actor))
		{
			if(ElectricBubble->bIsConnected)
			{
				return true;
			}
		}
	}
	return false;
}

void ATFM_SkeletalActor::Deactivate()
{
	if (bIsSwitchable || (bIsElectric && !IsConnected()))
	{
		if (bIsActive && DoorCloseSound)
			UGameplayStatics::PlaySoundAtLocation(this, DoorCloseSound, GetActorLocation());
		bIsActive = false;
		Door->SetHiddenInGame(false);
		Door->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//Mesh->PlayAnimation(AnimStateClose, false);
	}
}
