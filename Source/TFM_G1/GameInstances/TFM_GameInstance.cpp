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

bool UTFM_GameInstance::GetHeavyOn() 
{
	return bHeavyOn;
}
void UTFM_GameInstance::SetHeavyOn(bool NewHeavyOn)
{
	bHeavyOn = NewHeavyOn;
}
bool UTFM_GameInstance::GetAnchorOn()
{
	return bAnchorOn;
}
void UTFM_GameInstance::SetAnchorOn(bool NewAnchorOn)
{
	bAnchorOn = NewAnchorOn;
}
bool UTFM_GameInstance::GetAirOn()
{
	return bAirOn;
}
void UTFM_GameInstance::SetAirOn(bool NewAirOn)
{
	bAirOn = NewAirOn;
}
bool UTFM_GameInstance::GetSoapOn()
{
	return bSoapOn;
}
void UTFM_GameInstance::SetSoapOn(bool NewSoapOn)
{
	bSoapOn = NewSoapOn;
}
bool UTFM_GameInstance::GetMagneticOn()
{
	return bMagneticOn;
}
void UTFM_GameInstance::SetMagneticOn(bool NewMagneticOn)
{
	bMagneticOn = NewMagneticOn;
}