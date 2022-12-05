// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleAnchor.h"
#include "Components/BoxComponent.h"
#include "Actors/Bubbles/TFM_BubbleHeavy.h"
#include "Engine/EngineTypes.h"


ATFM_BubbleAnchor::ATFM_BubbleAnchor()
{
	Mesh->SetEnableGravity(false);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetSimulatePhysics(false);

	BoxCollider->BodyInstance.bLockZTranslation = true;
	BoxCollider->BodyInstance.bLockRotation = true;

	TopDetection->SetupAttachment(BoxCollider);

	Mesh->SetupAttachment(BoxCollider);
}

void ATFM_BubbleAnchor::ApplyForce(FVector Direction, float Force, int PushAttracValue)
{
	BoxCollider->AddForce(Direction * Force * PushAttracValue);
}

void ATFM_BubbleAnchor::EnablePhysics()
{

	if (!BoxCollider->IsSimulatingPhysics())
	{
		BoxCollider->SetSimulatePhysics(true);
	}
}

void ATFM_BubbleAnchor::DisablePhysics()
{
	BoxCollider->SetSimulatePhysics(false);
}

void  ATFM_BubbleAnchor::BeginPlay()
{
	Super::BeginPlay();
}

