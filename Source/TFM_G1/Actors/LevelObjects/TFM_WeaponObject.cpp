#include "Actors/LevelObjects/TFM_WeaponObject.h"
#include "Widget/TFM_BaseUserWidget.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
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

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	BoxCollider->SetupAttachment(RootComponent);
}

void ATFM_WeaponObject::BeginPlay()
{
	Super::BeginPlay();


	if (WidgetToOpen) {
		Widget = CreateWidget<UTFM_BaseUserWidget>(GetWorld()->GetFirstPlayerController(), WidgetToOpen);
		check(Widget);
		Widget->AddToPlayerScreen();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
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
		else if (MagneticOnPickUp)
		{
			Character->MagneticOn = true;
		}
		if (WeaponOnSound)
			UGameplayStatics::PlaySoundAtLocation(this, WeaponOnSound, GetActorLocation());
		WeaponMesh->SetVisibility(false);
		if(Widget)
			Widget->SetVisibility(ESlateVisibility::Visible);

		BoxCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &ATFM_WeaponObject::CloseTutorial);
		PickRadius->OnComponentBeginOverlap.RemoveDynamic(this, &ATFM_WeaponObject::BeginOverlap);
		
	}
}

void ATFM_WeaponObject::CloseTutorial(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Widget)
		Widget->SetVisibility(ESlateVisibility::Hidden);
	Destroy();
}

