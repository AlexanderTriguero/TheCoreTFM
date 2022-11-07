// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/TFM_AirGun.h"
#include "Components/CapsuleComponent.h"
#include "Actors/TFM_ActorBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"



ATFM_AirGun::ATFM_AirGun() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	VacuumCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Vacuum Collision"));
	VacuumCollision->SetupAttachment(ProjectilePosition);

}

void ATFM_AirGun::BeginPlay()
{
	Super::BeginPlay();

}

void ATFM_AirGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShooting)
	{
		TSet<AActor*> OverlappingActors;
		VacuumCollision->GetOverlappingActors(OverlappingActors);

		FHitResult OutHit;
		FVector Start = GetActorLocation();
		FVector Direction;
		FVector End;

		for (AActor* OtherActor : OverlappingActors)
		{
			ATFM_ActorBase* ActorBase = Cast<ATFM_ActorBase>(OtherActor);
			if (ActorBase && ActorBase->IsMovable())
			{
				End = ActorBase->GetMesh()->GetComponentLocation();
				UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery_MAX, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);
				Direction = UKismetMathLibrary::GetDirectionUnitVector(Start, End);
				if (ActorBase == OutHit.Actor)
				{
					ActorBase->GetMesh()->AddForce(Direction * Force * PushAttracValue);
				}
			}
		}
	}
}

void ATFM_AirGun::Shoot()
{
	if (!bIsShooting)
	{
		bIsShooting = true;
		PushAttracValue = 1;
	}
}
void ATFM_AirGun::ShootSecondary()
{
	if (!bIsShooting)
	{
		bIsShooting = true;
		PushAttracValue = -1;
	}
}

void ATFM_AirGun::StopShooting()
{
	bIsShooting = false;
}