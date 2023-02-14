// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleElectric.h"
#include "CableComponent.h"
#include "Actors/TFM_SkeletalActor.h"
#include "Actors/LevelObjects/TFM_PowerSource.h"
#include "Kismet/GameplayStatics.h"

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
	if(ConnectionSound && !bIsConnected)
		UGameplayStatics::PlaySoundAtLocation(this, ConnectionSound, GetActorLocation());
	bIsConnected = true;
	Mesh->SetMaterial(0, ConnectedMaterial);
}

void ATFM_BubbleElectric::Disconnect()
{
	DisconnectVisual();
	bFirstToSource = false;
	if (bIsConnected && DisconnectionSound)
		UGameplayStatics::PlaySoundAtLocation(this, DisconnectionSound, GetActorLocation());
	bIsConnected = false;
	Mesh->SetMaterial(0, DisconnectedMaterial);
}

void ATFM_BubbleElectric::Tick(float DeltaSeconds)
{
	CheckConnection();
	if (bIsConnected)
		PowerActorsOn();
}


void ATFM_BubbleElectric::ConnectToSource(ATFM_PowerSource* ExternalSource, bool SetToConnect)
{
	bIsConnectedToSource = SetToConnect;
	if (SetToConnect)
		PowerSource = ExternalSource;
	else
		DisconnectVisual();
}

void ATFM_BubbleElectric::ConnectVisual(AActor* actorToConnectTo)
{
	ConductionVisual->SetHiddenInGame(false);
	AActor* AttachEnd = actorToConnectTo;
	FName ComponentName;
	if (ATFM_PowerSource* PowerSourceConnection = Cast<ATFM_PowerSource>(AttachEnd))
	{
		ComponentName = FName("ConnectionPoint");
	}
	else
		ComponentName = FName("Mesh");
	ConductionVisual->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	ConductionVisual->CableLength = (AttachEnd->GetActorLocation() - GetActorLocation()).Size() - 100.f;
	ConductionVisual->SetAttachEndTo(AttachEnd, ComponentName);
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
					if (ElectricBubble->bIsConnected && ElectricBubble->BubbleConnection != this)
						BubbleConnection = ElectricBubble;
						Connect(ElectricBubble);
				}
			}
		}
		if(!bFirstToSource && BubbleConnection)
			ConnectVisual(BubbleConnection);
			
	} 
	if (bIsConnectedToSource)
	{
		ConnectVisual(PowerSource);
		bFirstToSource = true;
		return;
	}
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
