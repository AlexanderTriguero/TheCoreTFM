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

/* No hace falta implementarlo si no se van a modificar las físicas
void ATFM_BubbleBase::Tick(float DeltaTime)
{
	if (IsFalling)
	{
		TSet<AActor*> OverlappingActors;
		TopDetection->GetOverlappingActors(OverlappingActors);
		if (OverlappingActors.Num()<1)
		{
			IsFalling = false;
		}
	}
}
*/


void ATFM_BubbleBase::ApplyForce(FVector Direction, float Force, int PushAttracValue)
{
	Mesh->AddForce(Direction * Force * PushAttracValue);

}

void ATFM_BubbleBase::Explode()
{
	TSet<AActor*> OverlappingActors;
	//aveces da error porque this es nullptr, entonces nos aseguramos de que no pase esto
	if (this) {
		/* Se seleccionaban los objetos encima de la busbuja para devolverles las fisicas
		TopDetection->GetOverlappingActors(OverlappingActors);

		for (AActor* Actor : OverlappingActors)
		{
			if (ATFM_BubbleBase* Bubble = Cast<ATFM_BubbleBase>(Actor)) {
				Bubble->IsFalling =true;
				Bubble->EnablePhysics();
			}
		}*/
		Destroy();
	}
	
}

void ATFM_BubbleBase::Resize(TEnumAsByte<EBubbleSize> NewSize)
{
	Size = NewSize;
}

FVector ATFM_BubbleBase::GetPointToSpawn()
{
	return TopDetection->GetComponentLocation();
}

bool ATFM_BubbleBase::HasSomethingOnTop()
{
	TSet<AActor*> OverlappingActors;
	TopDetection->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor: OverlappingActors)
	{
		if (Actor->IsA<ATFM_BubbleBase>())
		{
			return true;
		}
	}
	return false;
	

}



// Called when the game starts or when spawned
void ATFM_BubbleBase::BeginPlay()
{
	Super::BeginPlay();

	/* Eventos utilizados para manejo de físicas
	Mesh->OnComponentHit.AddUniqueDynamic(this, &ATFM_BubbleBase::OnHit);
	TopDetection->OnComponentEndOverlap.AddUniqueDynamic(this, &ATFM_BubbleBase::OnComponentEndOverlap);
	*/
	
}
/* Metodos para menajo de físicas
void ATFM_BubbleBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsMoving && !IsFalling)
	{
		DisablePhysics();
	}
}

void ATFM_BubbleBase::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ATFM_BubbleBase* BubbleBase=Cast<ATFM_BubbleBase>(OtherActor))
	{
		BubbleBase->IsFalling = true;
		BubbleBase->EnablePhysics();
	}
}
*/

