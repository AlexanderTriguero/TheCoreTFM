// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/TFM_AirGun.h"
#include "Components/CapsuleComponent.h"
#include "Actors/TFM_ActorBase.h"
#include "Actors/Bubbles/TFM_BubbleAnchor.h"
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
						//Mientras se este empujando o atrayendo al actor, se estar? moviendo, de manera que aunque haga hit con el suelo las fisicas estar?n activas
						/*ActorBase->SetIsMoving(true);*/
					if (ActorBase->IsA<ATFM_BubbleAnchor>()) {
						ActorBase->EnablePhysics();	
					}
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


void ATFM_AirGun::onEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*Para que funcione con todos los actores
	if (ATFM_ActorBase* Actor = Cast<ATFM_ActorBase>(OtherActor))
	{
		//Como no est? en el collider de empujar, deja de moverse, de est? manera, el suelo podr? detener sus f?sicas
		Actor->SetIsMoving(false);

		//Cuando sea una AnchorBubble, se desactivan las fisicas para que la burbuja no se siga moviendo hasta el infinito
		if (ATFM_BubbleAnchor* Anchor= Cast<ATFM_BubbleAnchor>(Actor))
		{
			Anchor->DisablePhysics();
		}
	}
	*/

	// Para que funcione con los anchorBubble
	if (ATFM_BubbleAnchor* Anchor = Cast<ATFM_BubbleAnchor>(OtherActor))
	{
		Anchor->DisablePhysics();	
	}
}



