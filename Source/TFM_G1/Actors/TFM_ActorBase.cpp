// Fill out your copyright notice in the Description page of Project Settings.

#include "TFM_ActorBase.h"

#include "LevelObjects/TFM_SwitchFloor.h"

// Sets default values
ATFM_ActorBase::ATFM_ActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	RootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Root Point"));
	RootPoint->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned
void ATFM_ActorBase::BeginPlay()
{
	Super::BeginPlay();

}

UStaticMeshComponent* ATFM_ActorBase::GetMesh()
{
	return Mesh;
}

USceneComponent* ATFM_ActorBase::GetRootPoint()
{
	return RootPoint;
}

void ATFM_ActorBase::ApplyForce(FVector Direction, float Force, int PushAttracValue)
{
	Mesh->AddForce(Direction * Force * PushAttracValue);
}



void ATFM_ActorBase::EnablePhysics()
{
	if (!Mesh->IsSimulatingPhysics())
	{
		Mesh->SetSimulatePhysics(true);
	}
}
void ATFM_ActorBase::DisablePhysics()
{
	if (Mesh->IsSimulatingPhysics())
	{
		Mesh->SetSimulatePhysics(false);
	}
}

//No se van a modificar las fisicas de los objetos
/*
bool ATFM_ActorBase::GetIsIsMoving()
{
	return IsMoving;
}
void ATFM_ActorBase::SetIsMoving(bool NewIsMoving)
{
	if (NewIsMoving != IsMoving)
	{
		IsMoving = NewIsMoving;
	}
}
*/

bool ATFM_ActorBase::IsMovable()
{
	return bMovable;
}


