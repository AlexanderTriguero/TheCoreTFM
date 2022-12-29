// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleElectric.h"

#include "CableComponent.h"
#include "Actors/TFM_SkeletalActor.h"

ATFM_BubbleElectric::ATFM_BubbleElectric() : Super()
{
	ConductionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Conduction Sphere"));
	ConductionSphere->SetSphereRadius(ConductionRadius);
	ConductionSphere->SetupAttachment(Mesh);
	ConnectedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("Connected Material"));
	Mesh->SetMaterial(0, DisconnectedMaterial);
	Mesh->BodyInstance.bLockZTranslation = true;
	Mesh->BodyInstance.bLockRotation = true;
	ConductionVisual = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	ConductionVisual->SetupAttachment(RootComponent);
	ConductionVisual->bAttachStart = true;
	ConductionVisual->bAttachEnd = true;
	ConductionVisual->SetHiddenInGame(true);
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
	CheckConnection();
	if (bIsConnected)
		PowerActorsOn();
}


void ATFM_BubbleElectric::ConnectVisual(AActor* bubbleToConnectTo)
{
	ConductionVisual->SetHiddenInGame(false);
	AActor* AttachEnd = bubbleToConnectTo;
	ConductionVisual->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	ConductionVisual->CableLength = (AttachEnd->GetActorLocation() - GetActorLocation()).Size() - 100.f;
	ConductionVisual->SetAttachEndTo(AttachEnd, FName("Mesh"));
}

void ATFM_BubbleElectric::DisconnectVisual()
{
	ConductionVisual->SetHiddenInGame(true);
	ConductionVisual->CableLength = 0.f;
	ConductionVisual->SetAttachEndTo(this, FName("Mesh"));
}

void ATFM_BubbleElectric::CheckConnection()
{
	ConnectedBubbles.Empty();
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_BubbleElectric::StaticClass());
	if (Result.Num() != 0)
	{
		for (AActor* Actor : Result)
		{
			if (ATFM_BubbleElectric* ElectricBubble = Cast<ATFM_BubbleElectric>(Actor))
			{
				ConnectedBubbles.Add(ElectricBubble);
				for (ATFM_BubbleElectric* Bubble : ElectricBubble->ConnectedBubbles)
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
		ConnectVisual(ConnectedBubbles[0]);
	} else
	{
		DisconnectVisual();
	}
	if (bIsConnectedToSource)
		return;
	for (ATFM_BubbleElectric* Bubble : ConnectedBubbles)
	{
		if (Bubble->bIsConnectedToSource)
			return;
	}
	if (!bIsConnectedToSource)
		Disconnect();
}

void ATFM_BubbleElectric::PowerActorsOn()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, ATFM_SkeletalActor::StaticClass());
	for (AActor* Actor : Result)
	{
		if (ATFM_SkeletalActor* PowerableActor = Cast<ATFM_SkeletalActor>(Actor))
		{
			PowerableActor->Activate();
		}
	}
}
