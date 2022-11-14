// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleBase.h"

// Sets default values
ATFM_BubbleBase::ATFM_BubbleBase() :Super()
{
	bMovable = true;
	Mesh->SetSimulatePhysics(false);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->BodyInstance.bLockRotation = true;
}

void ATFM_BubbleBase::ApplyForce(FVector Direction, float Force, int PushAttracValue)
{
	Mesh->AddForce(Direction * Force * PushAttracValue);

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



