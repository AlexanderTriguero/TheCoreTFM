// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_DestructibleSurface.h"
#include "Actors/Bubbles/TFM_BubbleHeavy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATFM_DestructibleSurface::ATFM_DestructibleSurface()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(Mesh);

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
}

void ATFM_DestructibleSurface::DestroySelf()
{
	Destroy();
}


// Called when the game starts or when spawned
void ATFM_DestructibleSurface::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATFM_DestructibleSurface::OnComponentBeginOverlap);
}

// Called every frame
void ATFM_DestructibleSurface::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFM_DestructibleSurface::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATFM_BubbleHeavy* BubbleHeavy=Cast<ATFM_BubbleHeavy>(OtherActor))
	{
		float Speed = BubbleHeavy->GetMesh()->GetComponentVelocity().Size();

		if (Speed > DestroySpeed)
		{
			if (ShatterSound)
				UGameplayStatics::PlaySoundAtLocation(this, ShatterSound, GetActorLocation());
			BoxCollider->DestroyComponent();
			Mesh->DestroyComponent();
			FTimerHandle DebrisDeleteTimer;
			GetWorldTimerManager().SetTimer(DebrisDeleteTimer, this, &ATFM_DestructibleSurface::DestroySelf, 1.0f, false, 2.5f);
		}
	}
}