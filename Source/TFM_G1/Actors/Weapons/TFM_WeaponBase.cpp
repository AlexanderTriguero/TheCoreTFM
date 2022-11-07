// Fill out your copyright notice in the Description page of Project Settings.


#include "TFM_WeaponBase.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Components/SphereComponent.h"

// Sets default values
ATFM_WeaponBase::ATFM_WeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(WeaponMesh);
	ProjectilePosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectilePosition"));
	ProjectilePosition->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void ATFM_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATFM_WeaponBase::Shoot()
{
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	if(BubbleToSpawn != nullptr)
	{
		GetWorld()->SpawnActor<ATFM_BubbleBase>(BubbleToSpawn, ProjectilePosition->GetComponentTransform(), Params);
	}
}

void ATFM_WeaponBase::ShootSecondary()
{
}

void ATFM_WeaponBase::Reload()
{
	ChargePercent = 1.f;
}

