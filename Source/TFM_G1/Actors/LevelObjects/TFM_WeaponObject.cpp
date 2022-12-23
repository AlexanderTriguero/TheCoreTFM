#include "Actors/LevelObjects/TFM_WeaponObject.h"
#include "Components/SphereComponent.h"
#include "TFM_G1/TFM_G1Character.h"

ATFM_WeaponObject::ATFM_WeaponObject()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	PickRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Pick Radius"));
	PickRadius->SetupAttachment(RootComponent);

	PickRadius->OnComponentBeginOverlap.AddDynamic(this, &ATFM_WeaponObject::BeginOverlap);
}

void ATFM_WeaponObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATFM_WeaponObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATFM_WeaponObject::BeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	ATFM_G1Character* Character = Cast<ATFM_G1Character>(OtherActor);

	if (OtherActor == Character) 
	{
		if (HeavyOnPickUp) 
		{
			Character->HeavyOn = true;
		}else if(AnchorOnPickUp)
		{
			Character->AnchorOn = true;
		}
		else if (AirOnPickUp)
		{
			Character->AirOn = true;
		}
		else if (SoapOnPickUp)
		{
			Character->SoapOn = true;
		}
		else if (SoapOnPickUp)
		{
			Character->MagneticOn = true;
		}

		Destroy();
	}

	
}

