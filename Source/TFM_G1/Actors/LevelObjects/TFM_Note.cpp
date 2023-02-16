// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/LevelObjects/TFM_Note.h"
#include "Components/StaticMeshComponent.h"
#include "Widget/TFM_BaseUserWidget.h"
#include "Components/BoxComponent.h"
#include "TFM_G1Character.h"

ATFM_Note::ATFM_Note() :Super()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Note Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollider->SetupAttachment(Mesh);
}

void ATFM_Note::BeginPlay()
{
	Super::BeginPlay();
	if (NoteContentClass) {
		NoteContent = CreateWidget(GetWorld(), NoteContentClass);
		NoteContent->AddToPlayerScreen();
		APlayerController* A=NoteContent->GetOwningPlayer();
		NoteContent->SetVisibility(ESlateVisibility::Hidden);
	}
}


void ATFM_Note::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (NoteContentClass && Widget) {
		if (ATFM_G1Character* Player = Cast<ATFM_G1Character>(OtherActor)) {
			Widget->SetVisibility(ESlateVisibility::Visible);
			Player->SetNoteToRead(NoteContentClass);
		}
	}
}

void ATFM_Note::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
	if (Widget) {
		if (ATFM_G1Character* Player = Cast<ATFM_G1Character>(OtherActor)) {
			Widget->SetVisibility(ESlateVisibility::Hidden);
			Player->DisableRead();
		}
	}
}