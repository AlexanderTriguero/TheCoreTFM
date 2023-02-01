// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_TutorialCollider.h"
#include "Widget/TFM_BaseUserWidget.h"
#include "Components/BoxComponent.h"
#include "TFM_G1Character.h"


// Sets default values
ATFM_TutorialCollider::ATFM_TutorialCollider()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Trigger"));
	BoxCollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATFM_TutorialCollider::BeginPlay()
{
	Super::BeginPlay();	

	if (WidgetToOpen) {
		Widget = CreateWidget<UTFM_BaseUserWidget>(GetWorld()->GetFirstPlayerController(),WidgetToOpen);
		check(Widget);
		Widget->AddToPlayerScreen();
		if (ShowAtStart) {
			Widget->SetVisibility(ESlateVisibility::Visible);
			bActivable = false;
			bWidgetShowed = true;
		}
		else {
			Widget->SetVisibility(ESlateVisibility::Hidden);
			bActivable = true;
			bWidgetShowed = false;
		}
		
	}
	BoxCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ATFM_TutorialCollider::OnComponentBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddUniqueDynamic(this, &ATFM_TutorialCollider::OnComponentEndOverlap);		
}

void ATFM_TutorialCollider::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bActivable){	
		if (RequirementsSatisfied(OtherActor)) {
			Widget->SetVisibility(ESlateVisibility::Visible);
			bActivable = false;
			bWidgetShowed = true;
		}
	}
}
void ATFM_TutorialCollider::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<APawn>() && bWidgetShowed) {
		Widget->SetVisibility(ESlateVisibility::Hidden);
		bWidgetShowed=false;
	}
}

bool ATFM_TutorialCollider::RequirementsSatisfied(AActor* OtherActor) {
	if (ATFM_G1Character* Player = Cast<ATFM_G1Character>(OtherActor)) {
		if (bHeavyRequired && !Player->IsHeavyEquiped()) {
			return false;
		}
		if (bAnchorRequired && !Player->IsAnchorEquiped()) {
			return false;
		}
		if (bAirRequired && !Player->IsAirEquiped()) {
			return false;
		}
		if (bSoapRequired && !Player->IsSoapEquiped()) {
			return false;
		}
		if (bElectricRequired && !Player->IsMagneticEquiped()) {
			return false;
		}
		return true;
	}
	return false;
}


