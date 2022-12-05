// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/TFM_SwingingSoapWeapon.h"

#include "CableComponent.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

void ATFM_SwingingSoapWeapon::Shoot()
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
		SoapSpawned->SwitchEnd(OutHit.GetActor(), FName("Mesh"));
	}
}

void ATFM_SwingingSoapWeapon::ShootSecondary()
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
	TArray<AActor*> FoundSwingingSoaps;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATFM_SwingingSoap::StaticClass(), FoundSwingingSoaps);
	bSoapShot = FoundSwingingSoaps.Num() == 0;
	return(bSoapShot);
}
