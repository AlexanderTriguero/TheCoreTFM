#include "TFM_WeaponBase.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


ATFM_WeaponBase::ATFM_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);


	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereCollision->SetupAttachment(WeaponMesh);
	ProjectilePosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectilePosition"));
	ProjectilePosition->SetupAttachment(WeaponMesh);

	PositionToSpawnBubble = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PositionToSpawnBubble"));
	PositionToSpawnBubble->SetupAttachment(ProjectilePosition);
	PositionToSpawnBubble->SetVisibility(false);
	PositionToSpawnBubble->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned 
void ATFM_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->SetMobility(EComponentMobility::Movable);
	

}


void ATFM_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawningBubble) {		
		FVector SpawnPosition = ProjectilePosition->GetComponentLocation();
		FVector Start = ((ProjectilePosition->GetRightVector() * -100.f) + SpawnPosition);
		FVector End = ((ProjectilePosition->GetRightVector() * 100.f) + SpawnPosition);
		FHitResult OutHit;
		
		CheckIfCanSpawnBubble();

		UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);


		if (ATFM_BubbleBase* BubbleBase = Cast<ATFM_BubbleBase>(OutHit.GetActor()))
		{
			PositionToSpawnBubble->SetWorldLocation(BubbleBase->GetPointToSpawn());
		}
		else {
			PositionToSpawnBubble->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		}
	}
	
}


void ATFM_WeaponBase::Shoot()
{
	if (PositionToSpawnBubble && SpawnedBubbles.Num() < MaxSpawnedBubbles) {
		PositionToSpawnBubble->SetVisibility(true);
		bSpawningBubble = true;
	}
}

void ATFM_WeaponBase::StopShooting()
{
	if (SpawnedBubbles.Num() < MaxSpawnedBubbles)
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATFM_BubbleBase* SpawnedBubble;

		if (BubbleToSpawn != nullptr && bCanSpawnBubble)
		{
			FTransform ProjectileTransform = ProjectilePosition->GetComponentTransform();

			ProjectileTransform.SetLocation(PositionToSpawnBubble->GetComponentLocation());
			ProjectileTransform.SetRotation(FQuat(0, 0, 0, 0));

			SpawnedBubble = GetWorld()->SpawnActor<ATFM_BubbleBase>(BubbleToSpawn, ProjectileTransform, Params);
			if (SpawnedBubble) {
				SpawnedBubbles.Add(SpawnedBubble);
			}
		}
	}
	HideSpawnPreview();
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
	if (BubbleBase && !BubbleBase->bLevelAsset)
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


void ATFM_WeaponBase::StopShootingSecondary()
{

}


void ATFM_WeaponBase::Reload()
{
	ChargePercent = 1.f;
}


void ATFM_WeaponBase::CheckIfCanSpawnBubble()
{

	TSet<AActor*> OverlappingComponents;
	PositionToSpawnBubble->GetOverlappingActors(OverlappingComponents);

	if (OverlappingComponents.Num() > 0) {
		PositionToSpawnBubble->SetMaterial(0, CanNotSpawnMaterial);
		bCanSpawnBubble = false;
	}
	else {
		PositionToSpawnBubble->SetMaterial(0, CanSpawnMaterial);
		bCanSpawnBubble = true;
	}
}

void ATFM_WeaponBase::HideSpawnPreview()
{
	if (PositionToSpawnBubble) {
		PositionToSpawnBubble->SetVisibility(false);
		bSpawningBubble = false;
		bCanSpawnBubble = false;
		PositionToSpawnBubble->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	}
}

