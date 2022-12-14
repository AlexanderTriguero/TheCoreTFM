// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_SwitchFloor.h"

#include "TFM_G1Character.h"
#include "Actors/TFM_SkeletalActor.h"
#include "Components/BoxComponent.h"

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
	if (Cast<ATFM_ActorBase>(OtherActor) || Cast<ATFM_G1Character>(OtherActor))
	{
		DeactivateButton();
	}

}

void ATFM_SwitchFloor::ActivateButton()
{
	IsActive = true;
	if(RelatedActor)
	{
		RelatedActor->TryActivate();
	}
}

void ATFM_SwitchFloor::DeactivateButton()
{
	IsActive = false;
	if(RelatedActor)
	{
		RelatedActor->Deactivate();
	}
}
