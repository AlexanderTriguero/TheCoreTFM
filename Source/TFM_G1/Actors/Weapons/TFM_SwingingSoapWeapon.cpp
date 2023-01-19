// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/TFM_SwingingSoapWeapon.h"

#include "CableComponent.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

void ATFM_SwingingSoapWeapon::Shoot(ATFM_G1Character* CurrentCharacter)
{
	FHitResult OutHit;
	const FVector EndLocation = ProjectilePosition->GetComponentLocation() + ProjectilePosition->GetForwardVector() * 10000.f;
	UKismetSystemLibrary::LineTraceSingle(this, ProjectilePosition->GetComponentLocation(), EndLocation, TraceTypeQuery1, true, {}, EDrawDebugTrace::ForDuration, OutHit, true);
	if(OutHit.GetActor()->IsA(BubbleToGrabOnto) && CanShoot())
	{
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATFM_SwingingSoap* SwingingSoap = GetWorld()->SpawnActorDeferred<ATFM_SwingingSoap>(SoapToSpawn, OutHit.GetActor()->GetActorTransform(), OutHit.GetActor(), UGameplayStatics::GetPlayerPawn(GetWorld(), 0), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		SwingingSoap->AttachEnd = this;
		SwingingSoap->AttachStart = OutHit.GetActor();
		UGameplayStatics::FinishSpawningActor(SwingingSoap, OutHit.GetActor()->GetActorTransform());
		SoapSpawned = SwingingSoap;
	}
	else if(OutHit.GetActor()->IsA(BubbleToReleaseTo) && !CanShoot())
	{
		if(ATFM_BubbleHeavy* BubbleHeavy = Cast<ATFM_BubbleHeavy>(OutHit.GetActor()))
		{
			if (!BubbleHeavy->bLevelBox)
				return;
		}
		SoapSpawned->SwitchEnd(OutHit.GetActor(), FName("GrabPoint"));
	}
}

void ATFM_SwingingSoapWeapon::ShootSecondary(ATFM_G1Character* CurrentCharacter)
{
	if(SoapSpawned)
	{
		SoapSpawned->Constraint->BreakConstraint();
		SoapSpawned->Constraint->TermComponentConstraint();
		SoapSpawned->Destroy();
	}
}

bool ATFM_SwingingSoapWeapon::CanShoot()
{
	TArray<AActor*> FoundSwingingSoapsActors;
	TArray<ATFM_SwingingSoap*> SwingingSoaps;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFM_SwingingSoap::StaticClass(), FoundSwingingSoapsActors);
	for(AActor* FoundSoapActor : FoundSwingingSoapsActors)
	{
		if(ATFM_SwingingSoap* FoundSoap = Cast<ATFM_SwingingSoap>(FoundSoapActor))
		{
			if (!FoundSoap->bLevelSoap)
				SwingingSoaps.Add(FoundSoap);
		}
	}
	bSoapShot = SwingingSoaps.Num() == 0;
	return(bSoapShot);
}
