// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstances/TFM_GameInstance.h"


int32 UTFM_GameInstance::GetCurrentWeaponIndex()
{
	return CurrentWeaponIndex;
}

void UTFM_GameInstance::SetCurrentWeaponIndex(int32 NewIndex)
{
	CurrentWeaponIndex = NewIndex;
}