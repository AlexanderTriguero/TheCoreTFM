// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleElectric.h"

ATFM_BubbleElectric::ATFM_BubbleElectric() : Super()
{
	ConductionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Conduction Sphere"));
	ConductionSphere->SetSphereRadius(ConductionRadius);
	ConductionSphere->SetupAttachment(Mesh);
	ConnectedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Connected Material"));
	Mesh->SetMaterial(0, DisconnectedMaterial);
	Mesh->BodyInstance.bLockZTranslation = true;
	Mesh->BodyInstance.bLockRotation = true;
}

void ATFM_BubbleElectric::Connect(ATFM_ActorBase* ConnectTo)
{
	bIsConnected = true;
	Mesh->SetMaterial(0, ConnectedMaterial);
	//TODO: Draw cable between two connected bubbles.
}

void ATFM_BubbleElectric::Disconnect()
{
	//TODO: Show Animation for disconnection
	bIsConnected = false;
	Mesh->SetMaterial(0, DisconnectedMaterial);
}

void ATFM_BubbleElectric::Tick(float DeltaSeconds)
{
	ConnectedBubbles.Empty();
	if(bIsConnectedToSource)
		return;
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_BubbleElectric::StaticClass());
	for (AActor* Actor : Result)
	{
		if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(Actor))
		{
			ConnectedBubbles.Add(ElectricBubble);
			for(ATFM_BubbleElectric* Bubble : ElectricBubble->ConnectedBubbles)
			{
				if (!ConnectedBubbles.Contains(Bubble))
					ConnectedBubbles.Add(Bubble);
			}
			if (!bIsConnected)
			{
				if (ElectricBubble->bIsConnected)
					Connect(ElectricBubble);
			}
		}
	}
	for(ATFM_BubbleElectric* Bubble : ConnectedBubbles)
	{
		if (Bubble->bIsConnectedToSource)
			return;
	}
	if(!bIsConnectedToSource)
		Disconnect();
}
