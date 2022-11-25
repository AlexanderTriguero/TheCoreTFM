#include "Actors/LevelObjects/TFM_Seesaw.h"

ATFM_Seesaw::ATFM_Seesaw()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SeesawMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Seesaw Mesh"));
	SeesawMesh->SetupAttachment(RootComponent);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	SeesawPhysics = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Seesaw Physics Axis"));
	SeesawPhysics->SetupAttachment(RootComponent);
}

void ATFM_Seesaw::BeginPlay()
{
	Super::BeginPlay();

	

}

void ATFM_Seesaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

