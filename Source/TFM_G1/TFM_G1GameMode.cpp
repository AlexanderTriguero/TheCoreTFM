// Copyright Epic Games, Inc. All Rights Reserved.

#include "TFM_G1GameMode.h"
#include "TFM_G1HUD.h"
#include "TFM_G1Character.h"
#include "UObject/ConstructorHelpers.h"

ATFM_G1GameMode::ATFM_G1GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/TFM/Characters/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATFM_G1HUD::StaticClass();
}
