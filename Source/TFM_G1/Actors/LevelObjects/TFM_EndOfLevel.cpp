// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_EndOfLevel.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TFM_G1Character.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ATFM_EndOfLevel::ATFM_EndOfLevel() :Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATFM_EndOfLevel::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATFM_EndOfLevel::OnComponentBeginOverlap);
	
}

void ATFM_EndOfLevel::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ATFM_G1Character* Character= Cast<ATFM_G1Character>(OtherActor)) {
		if (LevelToLoad!="") {
			Character->SaveGameInstanceInfo();
			TArray<AActor*> FoundSwingingSoaps;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFM_SwingingSoap::StaticClass(), FoundSwingingSoaps);
			for (AActor* Actor : FoundSwingingSoaps)
			{
				ATFM_SwingingSoap* SwingingSoap = Cast<ATFM_SwingingSoap>(Actor);
				SwingingSoap->Constraint->BreakConstraint();
				SwingingSoap->Constraint->TermComponentConstraint();
				SwingingSoap->Destroy();
			}
			if (WarpSound)
				UGameplayStatics::PlaySoundAtLocation(this, WarpSound, GetActorLocation());
			GetWorldTimerManager().SetTimer(WarpTimer, this, &ATFM_EndOfLevel::ChangeLevel, 1.0f, false, WarpSound->Duration);
		}
	}
}

void ATFM_EndOfLevel::ChangeLevel()
{
	UGameplayStatics::OpenLevel(this, LevelToLoad);
}



