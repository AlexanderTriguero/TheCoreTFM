// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_SwitchFloor.h"

#include "TFM_G1Character.h"
#include "Actors/TFM_SkeletalActor.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ATFM_SwitchFloor::ATFM_SwitchFloor() : Super()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	BoxCollider->SetupAttachment(Mesh);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ATFM_SwitchFloor::OnComponentBeginOverlapOnSwitch);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ATFM_SwitchFloor::OnComponentEndOverlapOnSwitch);
	IsActive = false;
}

void ATFM_SwitchFloor::OnComponentBeginOverlapOnSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ATFM_ActorBase>(OtherActor) || Cast<ATFM_G1Character>(OtherActor))
	{
		ActivateButton();
	}
	
}

void ATFM_SwitchFloor::OnComponentEndOverlapOnSwitch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bool bPressingSwitch = false;
	if (Cast<ATFM_ActorBase>(OtherActor) || Cast<ATFM_G1Character>(OtherActor))
	{
		TSet<AActor*> OverlappingActors;
		BoxCollider->GetOverlappingActors(OverlappingActors);

		for (AActor* Actor: OverlappingActors) {
			if ((Actor->IsA<ATFM_ActorBase>() || Actor->IsA<ATFM_G1Character>()) && !Actor->IsA<ATFM_SwitchFloor>()) {
				bPressingSwitch = true;
				break;
			}
		}
		if (!bPressingSwitch) {
			DeactivateButton();
		}
	}

}

void ATFM_SwitchFloor::ActivateButton()
{
	if (SwitchOnSound)
		UGameplayStatics::PlaySoundAtLocation(this, SwitchOnSound, GetActorLocation());
	IsActive = true;
	if (LightIndicator)
		LightIndicator->SetEnabled(true);
	if(RelatedActors.Num()>0)
	{
		for(ATFM_SkeletalActor* RelatedActor : RelatedActors)
			RelatedActor->TryActivate();
	}
}

void ATFM_SwitchFloor::DeactivateButton()
{
	if (SwitchOffSound)
		UGameplayStatics::PlaySoundAtLocation(this, SwitchOffSound, GetActorLocation());
	IsActive = false;
	if (LightIndicator)
		LightIndicator->SetEnabled(false);
	if (RelatedActors.Num() > 0)
	{
		for (ATFM_SkeletalActor* RelatedActor : RelatedActors)
			RelatedActor->Deactivate();
	}
}
