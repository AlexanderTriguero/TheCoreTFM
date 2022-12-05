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
	if(OutHit.GetActor()->IsA(BubbleToGrabOnto) && !bSoapShot)
	{
		bSoapShot = true;
		FActorSpawnParameters Params;
		Params.Owner = this;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ATFM_SwingingSoap* SwingingSoap = GetWorld()->SpawnActorDeferred<ATFM_SwingingSoap>(SoapToSpawn, OutHit.GetActor()->GetActorTransform(), OutHit.GetActor(), UGameplayStatics::GetPlayerPawn(GetWorld(), 0), ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		SwingingSoap->AttachEnd = this;
		SwingingSoap->AttachStart = OutHit.GetActor();
		UGameplayStatics::FinishSpawningActor(SwingingSoap, OutHit.GetActor()->GetActorTransform());
		SoapSpawned = SwingingSoap;
	}
	else if(OutHit.GetActor()->IsA(BubbleToReleaseTo) && bSoapShot)
	{
		SoapSpawned->SwitchEnd(OutHit.GetActor(), FName("Mesh"));
	}
}

void ATFM_SwingingSoapWeapon::ShootSecondary()
{
	TArray<AActor*> FoundConstraints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), UPhysicsConstraintComponent::StaticClass(), FoundConstraints);
	for (AActor* Actor : FoundConstraints)
	{
		UPhysicsConstraintComponent* ConstComp = Cast<UPhysicsConstraintComponent>(Actor);
		ConstComp->TermComponentConstraint();
		ConstComp->DestroyComponent();
	}
	if(SoapSpawned)
	{
		SoapSpawned->Destroy();
		bSoapShot = false;
	}
}
