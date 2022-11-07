// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleBase.h"

// Sets default values
ATFM_BubbleBase::ATFM_BubbleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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



