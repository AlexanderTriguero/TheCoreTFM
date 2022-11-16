// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Bubbles/TFM_BubbleBase.h"
#include "Components/BoxComponent.h"


// Sets default values
ATFM_BubbleBase::ATFM_BubbleBase() :Super()
{
	bMovable = true;
	Mesh->SetSimulatePhysics(false);
	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->BodyInstance.bLockRotation = true;

	TopDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("Top Detection"));
	TopDetection->SetupAttachment(Mesh);
}

void ATFM_BubbleBase::ApplyForce(FVector Direction, float Force, int PushAttracValue)
{
	Mesh->AddForce(Direction * Force * PushAttracValue);

}

void ATFM_BubbleBase::Explode()
{
	TSet<AActor*> OverlappingActors;
	TopDetection->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor :OverlappingActors)
	{
		if (ATFM_BubbleBase* Bubble=Cast<ATFM_BubbleBase>(Actor)) {
			Bubble->EnablePhysics();
		}
	}
	Destroy();
}

void ATFM_BubbleBase::Resize(TEnumAsByte<EBubbleSize> NewSize)
{
	Size = NewSize;
}

// Called when the game starts or when spawned
void ATFM_BubbleBase::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentHit.AddUniqueDynamic(this, &ATFM_BubbleBase::OnHit);
	
}

void ATFM_BubbleBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsMoving)
	{
		DisablePhysics();
	}
}

