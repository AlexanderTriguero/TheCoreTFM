// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Weapons/TFM_AnchorWeapon.h"
#include "Actors/Bubbles/TFM_BubbleBase.h"

void ATFM_AnchorWeapon::ShootSecondary()
{
	/*for (ATFM_BubbleBase* CurrentBubble : SpawnedBubbles)
	{
		CurrentBubble->Explode();
	}
	SpawnedBubbles.Empty();
	*/

	if (SpawnedBubbles.Num() > 0)
	{
		ATFM_BubbleBase* CurrentBubble = SpawnedBubbles.Last();
		SpawnedBubbles.Remove(CurrentBubble);
		CurrentBubble->Destroy();
	}
}