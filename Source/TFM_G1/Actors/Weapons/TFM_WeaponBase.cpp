#include "TFM_WeaponBase.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Components/SphereComponent.h"

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
	ATFM_BubbleBase* SpawnedBubble;
	if(BubbleToSpawn != nullptr)
	{
		FTransform ProjectileTransform = ProjectilePosition->GetComponentTransform();
		ProjectileTransform.SetRotation(FQuat(0,0,0,0));
		SpawnedBubble=GetWorld()->SpawnActor<ATFM_BubbleBase>(BubbleToSpawn, ProjectileTransform, Params);
		SpawnedBubbles.Add(SpawnedBubble);
	}
}

void ATFM_WeaponBase::StopShooting()
{
}

void ATFM_WeaponBase::ShootSecondary()
{
}

void ATFM_WeaponBase::Reload()
{
	ChargePercent = 1.f;
}

