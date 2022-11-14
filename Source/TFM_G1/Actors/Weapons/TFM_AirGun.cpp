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
	VacuumCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATFM_AirGun::onBeginOverlap);
	VacuumCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ATFM_AirGun::onEndOverlap);

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
		FCollisionQueryParams CollisionParams;

		for (AActor* OtherActor : OverlappingActors)
		{
			ATFM_ActorBase* ActorBase = Cast<ATFM_ActorBase>(OtherActor);
			if (ActorBase && ActorBase->IsMovable())
			{
				End = ActorBase->GetMesh()->GetComponentLocation();
				UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);

				Direction = UKismetMathLibrary::GetDirectionUnitVector(Start, End);	
				//When pushing/pulling the height of the actor will not change
				Direction.Z = 0.0f;
					if (ActorBase == OutHit.Actor) 
					{
						ActorBase->ApplyForce(Direction, Force, PushAttracValue);
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

void ATFM_AirGun::StopShooting()
{
	bIsShooting = false;
}
void ATFM_AirGun::ShootSecondary()
{
	if (!bIsShooting)
	{
		bIsShooting = true;
		PushAttracValue = -1;
	}
}

void ATFM_AirGun::onBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATFM_ActorBase* Actor = Cast<ATFM_ActorBase>(OtherActor))
	{
		Actor->EnablePhysics();
	}
}

void ATFM_AirGun::onEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATFM_ActorBase* Actor = Cast<ATFM_ActorBase>(OtherActor))
	{
		Actor->DisablePhysics();
	}
}


