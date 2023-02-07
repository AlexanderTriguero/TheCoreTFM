// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/TFM_MenuGameMode.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"


ATFM_MenuGameMode::ATFM_MenuGameMode():Super()
{

}

void ATFM_MenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (MainWidgetClass) {
		MainWidget = CreateWidget(GetWorld(), MainWidgetClass);
		MainWidget->AddToViewport();

		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}