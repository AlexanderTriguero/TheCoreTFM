// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TFM_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TFM_G1_API UTFM_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
		int32 GetCurrentWeaponIndex();
	UFUNCTION()
		void SetCurrentWeaponIndex(int32 NewIndex);

private:
	int32 CurrentWeaponIndex = 0;
};
