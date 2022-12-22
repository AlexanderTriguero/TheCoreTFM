// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_PowerSource.h"

#include "Actors/Bubbles/TFM_BubbleElectric.h"
#include "Components/SphereComponent.h"

ATFM_PowerSource::ATFM_PowerSource()
{
	ConnectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Connection Radius"));
	ConnectionSphere->SetSphereRadius(ConnectionRadius);
	ConnectionSphere->SetupAttachment(Mesh);
	
}

void ATFM_PowerSource::OnComponentBeginOverlapOnPowerSource(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(OtherActor))
	{
		if (!ElectricBubble->bIsConnected)
		{
			ElectricBubble->Connect(this);
			ElectricBubble->bIsConnectedToSource = true;
		}
	}
}

void ATFM_PowerSource::OnComponentEndOverlapOnPowerSource(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(OtherActor))
	{
		if (ElectricBubble->bIsConnected)
		{
			ElectricBubble->Disconnect();
			ElectricBubble->bIsConnectedToSource = false;
		}
	}
}

void ATFM_PowerSource::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_BubbleElectric::StaticClass());
	for (AActor* Actor : Result)
	{
		if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(Actor))
		{
			if (!ElectricBubble->bIsConnected)
			{
				ElectricBubble->Connect(this);
				ElectricBubble->bIsConnectedToSource = true;
			}
		}
	}
	ConnectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATFM_PowerSource::OnComponentBeginOverlapOnPowerSource);
	ConnectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATFM_PowerSource::OnComponentEndOverlapOnPowerSource);
}
