// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_Portal.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATFM_Portal::ATFM_Portal(): Super()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	ParticleSystem->SetupAttachment(Mesh);
	BoxCollider->SetupAttachment(Mesh);
	

}