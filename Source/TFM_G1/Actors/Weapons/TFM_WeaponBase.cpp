// Fill out your copyright notice in the Description page of Project Settings.


#include "TFM_WeaponBase.h"

// Sets default values
ATFM_WeaponBase::ATFM_WeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Static Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ATFM_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATFM_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

