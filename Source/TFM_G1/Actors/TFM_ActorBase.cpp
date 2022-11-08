// Fill out your copyright notice in the Description page of Project Settings.


#include "TFM_ActorBase.h"

// Sets default values
ATFM_ActorBase::ATFM_ActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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
bool ATFM_ActorBase::IsMovable()
{
	return bMovable;
}
// Called every frame
void ATFM_ActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

