// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/TFM_AirGun.h"
#include "Components/CapsuleComponent.h"
#include "Actors/TFM_ActorBase.h"
#include "Actors/Bubbles/TFM_BubbleAnchor.h"
#include "Actors/Bubbles/TFM_BubbleElectric.h"
#include "Actors/Bubbles/TFM_BubbleHeavy.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"


ATFM_AirGun::ATFM_AirGun() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	VacuumCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Vacuum Collision"));
	VacuumCollision->SetupAttachment(ProjectilePosition);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComp->SetupAttachment(WeaponMesh);

	PushParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Push Particles"));
	PushParticles->SetupAttachment(ProjectilePosition);
	PullParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Pull Particles"));
	PullParticles->SetupAttachment(ProjectilePosition);
	if (PushParticles)
		PushParticles->SetVisibility(false);
	if (PullParticles)
		PullParticles->SetVisibility(false);

}

void ATFM_AirGun::BeginPlay()
{
	Super::BeginPlay();
	if (AirSound)
		AudioComp->SetSound(AirSound);
	VacuumCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ATFM_AirGun::onEndOverlap);
	PushParticles->ActivateSystem();
	PullParticles->ActivateSystem();
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
			if (ATFM_BubbleHeavy* BubbleHeavy = Cast<ATFM_BubbleHeavy>(OtherActor))
			{
				if (BubbleHeavy->bLevelBox)
					continue;
			}
			ATFM_ActorBase* ActorBase = Cast<ATFM_ActorBase>(OtherActor);
			if (ActorBase && ActorBase->IsMovable())
			{
				End = ActorBase->GetRootPoint()->GetComponentLocation();
				UKismetSystemLibrary::LineTraceSingle(this, Start, End, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);

				Direction = UKismetMathLibrary::GetDirectionUnitVector(Start, End);	
				//When pushing/pulling the height of the actor will not change
				Direction.Z = 0.0f;
				if (ActorBase == OutHit.Actor) 
				{
						//Mientras se este empujando o atrayendo al actor, se estará moviendo, de manera que aunque haga hit con el suelo las fisicas estarán activas
						/*ActorBase->SetIsMoving(true);*/
					if (ActorBase->IsA<ATFM_BubbleAnchor>() || ActorBase->IsA<ATFM_BubbleElectric>()) {
						ActorBase->EnablePhysics();	
					}
					if(ATFM_BubbleAnchor* AnchorBubble = Cast<ATFM_BubbleAnchor>(ActorBase))
					{
						if(AnchorBubble->HasSomethingOnTop())
						{
							for(AActor* TopActor : AnchorBubble->TopActors())
							{
								if(ATFM_BubbleBase* TopBubble = Cast<ATFM_BubbleBase>(TopActor))
								{
									TopBubble->bIsOnTop = true;
								}
							}
						}
					}

					if(ATFM_BubbleBase* BaseBubble = Cast<ATFM_BubbleBase>(ActorBase))
					{
						if (BaseBubble->bIsOnTop)
							continue;
					}
					ActorBase->ApplyForce(Direction, Force, PushAttracValue);
				}			
			}
		}
	}
}

void ATFM_AirGun::Shoot(ATFM_G1Character* CurrentCharacter)
{
	if (!bIsShooting)
	{
		AudioComp->Play();
		bIsShooting = true;
		if (PushParticles)
			PushParticles->SetVisibility(true);
		PushAttracValue = 1;
	}
}

void ATFM_AirGun::StopShooting(ATFM_G1Character* CurrentCharacter)
{
	AudioComp->Stop();
	bIsShooting = false;
	if(PushParticles)
		PushParticles->SetVisibility(false);
}
void ATFM_AirGun::ShootSecondary(ATFM_G1Character* CurrentCharacter)
{
	if (!bIsShooting)
	{
		AudioComp->Play();
		bIsShooting = true;
		if (PullParticles)
			PullParticles->SetVisibility(true);
		PushAttracValue = -1;
	}
}
void ATFM_AirGun::StopShootingSecondary()
{
	AudioComp->Stop();
	bIsShooting = false;
	if (PullParticles)
		PullParticles->SetVisibility(false);

}


void ATFM_AirGun::onEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*Para que funcione con todos los actores
	if (ATFM_ActorBase* Actor = Cast<ATFM_ActorBase>(OtherActor))
	{
		//Como no está en el collider de empujar, deja de moverse, de está manera, el suelo podrá detener sus físicas
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
	if (ATFM_BubbleElectric* Electric = Cast<ATFM_BubbleElectric>(OtherActor))
	{
		Electric->DisablePhysics();
	}
}



