// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_PowerSource.h"

#include "Actors/Bubbles/TFM_BubbleElectric.h"
#include "Components/SphereComponent.h"

ATFM_PowerSource::ATFM_PowerSource()
{
	PrimaryActorTick.bCanEverTick = true;
	ConnectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Connection Radius"));
	ConnectionSphere->SetSphereRadius(ConnectionRadius);
	ConnectionSphere->SetupAttachment(Mesh);
	ConnectionPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Connection Point"));
	ConnectionPoint->SetupAttachment(Mesh);
	
}


void ATFM_PowerSource::OnComponentEndOverlapOnPowerSource(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(OtherActor))
	{
		if (ElectricBubble->bIsConnected)
		{
			ElectricBubble->Disconnect();
			ElectricBubble->ConnectToSource(this, false);
		}
	}
}

void ATFM_PowerSource::BeginPlay()
{
	Super::BeginPlay();
	ConnectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATFM_PowerSource::OnComponentEndOverlapOnPowerSource);
}

void ATFM_PowerSource::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_BubbleElectric::StaticClass());
	if (Result.Num() != 0)
	{
		if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(Result[0]))
		{
			if (!ElectricBubble->bIsConnected)
			{
				ElectricBubble->Connect(this);
				ElectricBubble->ConnectToSource(this, true);
				return;
			}
		}
	}
}


