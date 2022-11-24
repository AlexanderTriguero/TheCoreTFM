#include "TFM_WeaponBase.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Kismet/KismetSystemLibrary.h"
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
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ATFM_BubbleBase* SpawnedBubble;
	bool bSpawnBubble = true;

	if(BubbleToSpawn != nullptr)
	{
		FTransform ProjectileTransform = ProjectilePosition->GetComponentTransform();
		FVector SpawnPosition = ProjectilePosition->GetComponentLocation();
		ProjectileTransform.SetRotation(FQuat(0,0,0,0));
		FHitResult OutHit;
		FVector Direction;
		FVector Start = ((ProjectilePosition->GetRightVector() * -100.f) + SpawnPosition);
		FVector End = ((ProjectilePosition->GetRightVector() * 100.f) + SpawnPosition);
		FCollisionQueryParams CollisionParams;
		UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);

		if (ATFM_BubbleBase* BubbleBase=Cast<ATFM_BubbleBase>(OutHit.GetActor()))
		{
			bSpawnBubble = !BubbleBase->HasSomethingOnTop();
			ProjectileTransform.SetLocation(BubbleBase->GetPointToSpawn());
		}

		if (bSpawnBubble)
		{
			SpawnedBubble = GetWorld()->SpawnActor<ATFM_BubbleBase>(BubbleToSpawn, ProjectileTransform, Params);
		}
		
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

