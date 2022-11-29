// Fill out your copyright notice in the Description page of Project Settings.


#include "TFM_SwingingSoap.h"
#include "Actors/SwingingSoap/TFM_SwingingSoap.h"
#include "CableComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ATFM_SwingingSoap::ATFM_SwingingSoap() : Super()
{
	Cable = CreateDefaultSubobject<UCableComponent>(TEXT("Cable"));
	Cable->SetupAttachment(RootComponent);
	Constraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Constraint"));
	Constraint->SetupAttachment(Cable);

	Cable->bAttachStart = true;
	Cable->bAttachEnd = true;
}

void ATFM_SwingingSoap::SwitchEnd(AActor* newAttachEnd, FName ComponentName)
{
	AttachEnd = newAttachEnd;
	Cable->CableLength = (AttachEnd->GetActorLocation() - GetActorLocation()).Size() - 100.f;
	Cable->SetAttachEndTo(newAttachEnd, ComponentName);
}

// Called when the game starts or when spawned
void ATFM_SwingingSoap::BeginPlay()
{
	Super::BeginPlay();
	Cable->SetAttachEndTo(AttachEnd, FName("ProjectilePosition"));
	Cable->AttachToComponent(AttachStart->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	Cable->CableLength = (AttachEnd->GetActorLocation() - GetActorLocation()).Size() - 100.f;
	Constraint->ConstraintActor1 = this;
	Constraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, 45.f);
	Constraint->ConstraintActor2 = AttachEnd;
	Constraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, 45.f);
	Constraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Limited, Cable->CableLength);
	Constraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Limited, Cable->CableLength);
	Constraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, Cable->CableLength);
}
