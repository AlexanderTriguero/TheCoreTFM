// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleHeavy.h"

#include "Components/BoxComponent.h"

ATFM_BubbleHeavy::ATFM_BubbleHeavy() : Super()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxCollider->SetupAttachment(Mesh);
}
