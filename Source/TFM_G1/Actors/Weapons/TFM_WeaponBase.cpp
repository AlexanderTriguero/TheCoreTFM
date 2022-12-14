#include "TFM_WeaponBase.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

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
	if (SpawnedBubbles.Num()< MaxSpawnedBubbles)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATFM_BubbleBase* SpawnedBubble;
		bool bSpawnBubble = true;

		if (BubbleToSpawn != nullptr)
		{
			FTransform ProjectileTransform = ProjectilePosition->GetComponentTransform();
			FVector SpawnPosition = ProjectilePosition->GetComponentLocation();
			ProjectileTransform.SetRotation(FQuat(0, 0, 0, 0));
			FHitResult OutHit;
			FVector Direction;
			FVector Start = ((ProjectilePosition->GetRightVector() * -100.f) + SpawnPosition);
			FVector End = ((ProjectilePosition->GetRightVector() * 100.f) + SpawnPosition);
			FCollisionQueryParams CollisionParams;
			UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);

			if (ATFM_BubbleBase* BubbleBase = Cast<ATFM_BubbleBase>(OutHit.GetActor()))
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
}

void ATFM_WeaponBase::StopShooting()
{
}

void ATFM_WeaponBase::ShootSecondary()
{
	//Provisional, para poder explotar las HeavyBubbles
	/*for (ATFM_BubbleBase* CurrentBubble : SpawnedBubbles)
	{
		CurrentBubble->Explode();
	}
	SpawnedBubbles.Empty();
	*/
	FVector SpawnPosition = ProjectilePosition->GetComponentLocation();
	FVector Start = ((ProjectilePosition->GetRightVector() * -100.f) + SpawnPosition);
	FVector End = ((ProjectilePosition->GetRightVector() * 1000.f) + SpawnPosition);
	FHitResult OutHit;
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);
	ATFM_BubbleBase* BubbleBase = Cast<ATFM_BubbleBase>(OutHit.GetActor());
	if (BubbleBase)
	{
		TArray<AActor*> FoundSwingingSoaps;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFM_SwingingSoap::StaticClass(), FoundSwingingSoaps);
		for (AActor* Actor : FoundSwingingSoaps)
		{
			ATFM_SwingingSoap* SwingingSoap = Cast<ATFM_SwingingSoap>(Actor);
			if (SwingingSoap->AttachEnd == BubbleBase || SwingingSoap->AttachStart == BubbleBase)
			{
				SwingingSoap->Constraint->BreakConstraint();
				SwingingSoap->Constraint->TermComponentConstraint();
				SwingingSoap->Destroy();
			}
		}
		SpawnedBubbles.Remove(BubbleBase);
		BubbleBase->Destroy();
	}

}

void ATFM_WeaponBase::Reload()
{
	ChargePercent = 1.f;
}


