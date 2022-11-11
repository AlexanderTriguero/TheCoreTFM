// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleAnchor.h"
#include "Components/BoxComponent.h"

ATFM_BubbleAnchor::ATFM_BubbleAnchor()
{
	Mesh->SetEnableGravity(false);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(BoxCollider);
}