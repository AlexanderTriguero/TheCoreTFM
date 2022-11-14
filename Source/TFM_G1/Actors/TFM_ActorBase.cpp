// Fill out your copyright notice in the Description page of Project Settings.

#include "TFM_ActorBase.h"

// Sets default values
ATFM_ActorBase::ATFM_ActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);


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

void ATFM_ActorBase::ApplyForce(FVector Direction, float Force, int PushAttracValue)
{
	Mesh->AddForce(Direction * Force * PushAttracValue);
}

void ATFM_ActorBase::EnablePhysics()
{
	Mesh->SetSimulatePhysics(true);
}
void ATFM_ActorBase::DisablePhysics()
{
	Mesh->SetSimulatePhysics(false);
}

bool ATFM_ActorBase::IsMovable()
{
	return bMovable;
}
// Called every frame
void ATFM_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

