// Fill out your copyright notice in the Description page of Project Settings.


#include "TFM_SwingingSoap.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicsField/PhysicsFieldComponent.h"

// Sets default values
ATFM_SwingingSoap::ATFM_SwingingSoap() : Super()
{
	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	Cable->SetupAttachment(RootComponent);
	//Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
	//Constraint->SetupAttachment(Cable);

	Cable->bAttachStart = true;
	Cable->bAttachEnd = true;
}

void ATFM_SwingingSoap::SwitchEnd(AActor* newAttachEnd, FName ComponentName)
{
	AttachEnd = newAttachEnd;
	Cable->CableLength = (AttachEnd->GetActorLocation() - GetActorLocation()).Size() - 100.f;
	Cable->SetAttachEndTo(newAttachEnd, ComponentName);
	SetConstraints();
}

// Called when the game starts or when spawned
void ATFM_SwingingSoap::BeginPlay()
{
	Super::BeginPlay();
	Cable->SetAttachEndTo(AttachEnd, FName("ProjectilePosition"));
	Cable->AttachToComponent(AttachStart->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	Cable->CableLength = (AttachEnd->GetActorLocation() - GetActorLocation()).Size() - 100.f;
	
}

void ATFM_SwingingSoap::SetConstraints()
{
	UPhysicsConstraintComponent* ConstraintComp = NewObject<UPhysicsConstraintComponent>(AttachStart);
	ConstraintComp->ConstraintActor1 = AttachStart;
	ConstraintComp->ConstraintActor2 = AttachEnd;
	ConstraintComp->SetLinearXLimit(ELinearConstraintMotion::LCM_Limited, Cable->CableLength);
	ConstraintComp->SetLinearYLimit(ELinearConstraintMotion::LCM_Limited, Cable->CableLength);
	ConstraintComp->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, Cable->CableLength);
	ConstraintComp->InitComponentConstraint();
}
