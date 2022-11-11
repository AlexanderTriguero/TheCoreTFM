// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleBase.h"

// Sets default values
ATFM_BubbleBase::ATFM_BubbleBase() :Super()
{
	bMovable = true;
	Mesh->SetSimulatePhysics(true);
	Mesh->SetMobility(EComponentMobility::Movable);
}

void ATFM_BubbleBase::Explode()
{
	Destroy();
}

void ATFM_BubbleBase::Resize(TEnumAsByte<EBubbleSize> NewSize)
{
	Size = NewSize;
}

// Called when the game starts or when spawned
void ATFM_BubbleBase::BeginPlay()
{
	Super::BeginPlay();
	
}



