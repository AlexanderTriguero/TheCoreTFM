// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TFM_MenuGameMode.generated.h"

class UUserWidget;
UCLASS()
class TFM_G1_API ATFM_MenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATFM_MenuGameMode();

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MainWidgetClass = nullptr;

	UPROPERTY()
		UUserWidget* MainWidget = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
